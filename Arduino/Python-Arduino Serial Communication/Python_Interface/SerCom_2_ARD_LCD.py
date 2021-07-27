import serial # Serial imported for Serial communication
import time  # Required to use delay functions

ard_ser = serial.Serial('COM3', 9600, timeout=2)  # Create Serial port object called arduino SerialData
time.sleep(1) #give the connection a second to settle
i = 0
while True:
    py_msg_string = input("What would you like Ardy to Print?")
    #print(py_msg_string)
    ard_ser.write(py_msg_string.encode())
    i = i+1
    time.sleep(1)
    data = ard_ser.readline()[:-2]  #the last bit gets rid of the new-line chars
    if data:
        try:
            print(data.rstrip('\n'))
        except:
            print(data)


