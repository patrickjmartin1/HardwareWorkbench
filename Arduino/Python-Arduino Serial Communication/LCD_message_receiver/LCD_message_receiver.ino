/*
  Based off of:
  ---------------------------------
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
    ---------------------------------
    
  This script initializes the arduino with the LCD library. It The 
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

char ready_string[] = "WAITING FOR MSG";
//char msg_string[] = "HI FROM ARDY TO PY!";
char no_msgs_yet[] = "NO MSGS RECEIVED";
char msg_rcvd[] = "NEW MESSAGE";
char confirmation_message = "MSG RCVD";
const int buzzerPin = 9;    // connect the buzzer to pin 9
const int buzzLength = 6;  // sets the number of different buzz tones
char notes[buzzLength] = {
  'e', 'f', 'e', 'f', 'e', 'f'};

int beats[buzzLength] = {
  1, 1, 1, 1, 1, 1};

int tempo = 1000;
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
  lcd.setCursor(0, 0);  // Set the cursor to the position
  lcd.print(ready_string); // Display a message on the LCD!
  lcd.setCursor(0, 1);  // Set the cursor to the position
  lcd.print(no_msgs_yet);    

  // Setup buzzer 
  pinMode(buzzerPin, OUTPUT);  // sets the  buzzer pin as an OUTPUT
}

//// Loop Function //// 
void loop()
{

//  delay(300);
//  lcd.setCursor(0, 1); 
//  lcd.print("                "); // Erase the bottom row of text
//  delay(300);

  if(Serial.available() > 0) //Check to see if there is data available in the serial receive buffer 
  {
    
    // Let's have ARDY tell us a new message was received 
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print(msg_rcvd);

    // Let's play a sound to get someone's attention! 
    int i, duration;
    for (i = 0; i < buzzLength; i++) // for loop is used to index through the arrays
    {
      duration = beats[i] * tempo;  // length of note/rest in ms

      if (notes[i] == ' ')          // is this a rest? 
        delay(duration);            // then pause for a moment
      else                          // otherwise, play the note
      {
        tone(buzzerPin, frequency(notes[i]), duration);
        delay(duration);            // wait for tone to finish
      }
    delay(tempo/10);              // brief pause between notes
    }
    
    
    lcd.setCursor(0, 1); 
    lcd.print("                "); // Erase the bottom row of text
    delay(1000);
    
    // For loop to read from serial and recreate the original message
    char str_1[17];
    char str_2[17];
    char data;

    // Parse the incoming string into two lines
    for ( int i = 0; i < 16; i = i + 1)
    {
      // Loop through the 16 bytes of the message, and append to 'str'
      data = Serial.read();    
      str_1[i] = data;
    }
    
    for ( int i = 0; i < 16; i = i + 1)
    {
      // Loop through the 16 bytes of the message, and append to 'str'
      data = Serial.read();    
      str_2[i] = data;
    }
    
    str_1[16] = '\0';
    str_2[16] = '\0';

    // Send a confirmation message back 
    Serial.print("ARDY rcvd msg");
    //Serial.print(str_1);
    //Serial.print(str_2);

    // Print the data to the lcd
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print(str_1);
    lcd.setCursor(0, 10); 
    lcd.print(str_2);      
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

int frequency(char note) 
{
  int i;
  const int numNotes = 8;  // number of notes we're storing
  char names[numNotes] = { 
    'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'    };
  int frequencies[numNotes] = {
    262, 294, 330, 349, 392, 440, 494, 523    };

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency and exit function.
    }
  }
  return(0);  // We looked through everything and didn't find it,
  // but we still need to return a value, so return 0.
}
