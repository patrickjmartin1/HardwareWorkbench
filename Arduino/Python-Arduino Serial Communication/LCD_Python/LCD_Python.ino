/*
  SparkFun Inventor's Kit
  Example sketch 15

  LIQUID CRYSTAL DISPLAY (LCD)

  A Liquid Crystal Display (LCD) is a sophisticated module
  that can be used to display text or numeric data. The display
  included in your SIK features two lines of 16 characters, and
  a backlight so it can be used at night.

  If you've been using the Serial Monitor to output data,
  you'll find that a LCD provides many of the same benefits
  without needing to drag a large computer around.

  This sketch will show you how to connect an LCD to your Arduino
  and display any data you wish.


  This sketch was written by SparkFun Electronics,
  with lots of help from the Arduino community.
  This code is completely free for any use.
  Visit http://learn.sparkfun.com/products/2 for SIK information.
  Visit http://www.arduino.cc to learn about the Arduino.

  Version 1.0 2/2013 MDG
*/

// Load the LiquidCrystal library, which will give us
// commands to interface to the LCD:

#include <LiquidCrystal.h>

// Initialize the library with the pins we're using.
// (Note that you can use different pins if needed.)
// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Set the starting string which will display that we are waiting for data

char ready_string[] = "WAITING";
char msg_string[] = "HI FROM ARDY TO PY!";
// char data = " ";

//// Setup Function //// 
void setup()
{
  // Setup LED for troubleshooting
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);  
  // Open serial port for communication
  Serial.begin(9600);

  // Setup LCD screen
  lcd.begin(16, 2); //Initialize the 16x2 LCD
  lcd.clear();	//Clear any old data displayed on the LCD
  lcd.print(ready_string); // Display a message on the LCD!
}

void loop()
{

  // Write string to from Ardy to Serial Port  
  Serial.println(msg_string); // write a string

  //Write this message to the LCD then delete it
  lcd.setCursor(0, 1);  // Set the cursor to the position
  lcd.print(msg_string);    
  delay(300);
  lcd.setCursor(0, 1); 
  lcd.print("                "); // Erase the bottom row of text
  delay(300);

  if(Serial.available() > 0) 
  {
    // For loop to read from serial and recreate the original message
    char str[17];
    char data;
    for ( int i = 0; i < 16; i = i + 1)
    {
      // Loop through the 16 bytes of the message, and append to 'str'
      data = Serial.read();    
      str[i] = data;
    }
    
    str[16] = '\0';
    Serial.print(str);
    lcd.setCursor(0, 1); 
    lcd.print(str);    
    delay(300);
    lcd.setCursor(0, 1); 
    lcd.print("                "); // Erase the largest possible number
    delay(100);
  }
    /*
    digitalWrite(13,LOW);
    delay(5000);
    //Serial.print("ser_b_s_avail");
    lcd.setCursor(0, 0);
    lcd.print("ser com rec");
    if(Serial.read() == 1)
    {
      lcd.setCursor(0, 1);   //Set the (invisible) cursor to column 0,
  // row 1.
      lcd.print("1");
      
      lcd.setCursor(0, 1);  // Set the cursor to the position
      lcd.print("                "); // Erase the largest possible number
      */

}  
