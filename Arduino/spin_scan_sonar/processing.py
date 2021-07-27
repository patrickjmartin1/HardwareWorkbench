import serial # Serial imported for Serial communication
import time  # Required to use delay functions
import numpy as np
import matplotlib.pyplot as plt

class SpinScanSonarProcess():
    def __init__(self):
        self.angle_range_dict = {}

        self.serial_conn = serial.Serial('COM3', 9600, timeout=2)  # Create Serial port object called arduino SerialData
        time.sleep(1)  # give the connection a second to settle

        # Blank data placeholder
        self.data = []
        self.angles = np.array([])
        self.distances = np.array([])

        # Setup plotting
        plt.ion()
        self.fig, self.ax = plt.subplots(subplot_kw={'projection': 'polar'})
        self.lines = self.ax.plot(0, 0)

    def get_angle_range(self):
        data_b = self.serial_conn.readline()  # the last bit gets rid of the new-line chars
        return data_b

    def parse_data(self, data_b):
        self.data = data_b.decode("utf-8")
        return 0

    def data_to_dict(self):
        msg_split = self.data.split()
        if len(msg_split) < 6:
            return -1
        try:
            angle = float(msg_split[1])
            dist = float(msg_split[3])
            if dist == 2282.0:
                return -1
            self.angle_range_dict.update({angle:dist })
        except IndexError:
            return -1
        return 0

    def get_data(self):
        data_b = self.get_angle_range()
        self.parse_data(data_b)

    def main_func(self):
        while True:
            self.get_data()
            if self.data:
                try:
                    print(self.data.rstrip('\n'))
                    print('\n')
                except:
                    pass
                self.data_to_dict()
                print(self.angle_range_dict)
                self.update_plot()

    def get_angle_dist_vectors(self):
        deg_angles = np.array(list(self.angle_range_dict.keys()))
        self.angles = np.radians(deg_angles)
        self.distances = np.array(list(self.angle_range_dict.values()))

    def update_plot(self):
        # Remove the previous line
        self.ax.lines.pop(0)
        self.get_angle_dist_vectors()
        self.ax.plot(self.angles, self.distances)
        self.fig.canvas.draw()
        self.fig.canvas.flush_events()


if __name__ == "__main__":
    SSSP = SpinScanSonarProcess()
    SSSP.main_func()



