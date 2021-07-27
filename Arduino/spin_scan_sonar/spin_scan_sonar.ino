/*  
 *   spin_can_sonar
 *   
 *   This sketch will: 
 *      - Drive a stepper motor to scan over a range of angles, and... 
 *      - Use the sonic range finder to determine the range to the nearest object at each angle
 *      
 *   We will pass output from the arduino back to the computer via serial for visualizing in python
 *   
*/

#include "SR04.h"
#include <Stepper.h>

#define TRIG_PIN 4
#define ECHO_PIN 5
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);  // Create sonar object
long dist;                            // Variable for storing distance @ a given position 
float phi;                             // Position in degrees @ some point in time 
int current_step;                     // Variable for holding the current step (integer)
int step_size;                        // Variable for assigning step size 
char serial_buffer[128];               // Serial message buffer 
char angle_buffer[10];
char dist_buffer[10];
char step_buffer[10];

const int stepsPerRevolution = 2048;            // change this to fit the number of steps per revolution
const int steps_max = stepsPerRevolution / 2;   // Max number of steps - let's keep this as 0-180 deg. 
const int rolePerMinute = 15;                   // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int step_size_mag = 16;                             // Size of a single step 
const int step_start = 0;


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  myStepper.setSpeed(rolePerMinute);
  current_step = 0;
  delay(1000);
  step_size = step_size_mag;
}

void loop() {
  // Get the range @ current angle and print
  dist = sr04.Distance();
  float phi = (360 * (float)current_step) / (float)stepsPerRevolution;

  // Print the current location
  sprintf(serial_buffer, "angle: %s dist: %s step: %s", dtostrf(phi, 3, 2, angle_buffer), dtostrf(dist, 3, 2, dist_buffer), dtostrf(current_step, 3, 2, step_buffer));
  Serial.println(serial_buffer);

  // Move to the next position
  if ((current_step >= steps_max) && (step_size > 0))
  {
    // If we are at the end of the range, go back to beginning
    step_size = -step_size_mag;
  }
  else if ((current_step <= 0) && (step_size < 0))
  {
    step_size = step_size_mag;
  }

  myStepper.step(step_size);
  current_step = current_step + step_size;
  
}
