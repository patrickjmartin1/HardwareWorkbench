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

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int step_size = 64;              // Size of a single step 
const int step_start = 0;


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  myStepper.setSpeed(rolePerMinute);
  current_step = 0;
  delay(1000);
  
}

void loop() {
  // Get the range @ current angle and print
  dist = sr04.Distance();
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.print("\n");

  // Print the current location
  float phi = (360 * (float)current_step) / (float)stepsPerRevolution;
  Serial.print("Current Step: ");
  Serial.print(current_step);
  Serial.print("\n");
  Serial.print("Angle (deg.): ");
  Serial.print(phi);
  Serial.print("\n");

  // Move to the next position
  if (current_step >= stepsPerRevolution)
  {
    // If we are at the end of the range, go back to beginning
    myStepper.step(-stepsPerRevolution);
    current_step = 0;
  }
  else
  {
    myStepper.step(step_size);
    current_step = current_step + step_size;
  }
  
}
