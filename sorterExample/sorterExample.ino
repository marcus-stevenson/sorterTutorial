/*
  Library for the MMA8452Q
  By: Jim Lindblom and Andrea DeVore
  SparkFun Electronics
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/14587
  This sketch uses the SparkFun_MMA8452Q library to initialize
  the accelerometer and stream calcuated x, y, z, acceleration
  values from it (in g units).
  Hardware hookup:
  Arduino --------------- MMA8452Q Breakout
    3.3V  ---------------     3.3V
    GND   ---------------     GND
  SDA (A4) --\/330 Ohm\/--    SDA
  SCL (A5) --\/330 Ohm\/--    SCL
  The MMA8452Q is a 3.3V max sensor, so you'll need to do some
  level-shifting between the Arduino and the breakout. Series
  resistors on the SDA and SCL lines should do the trick.
  License: This code is public domain, but if you see me
  (or any other SparkFun employee) at the local, and you've
  found our code helpful, please buy us a round (Beerware
  license).
  Distributed as is; no warrenty given.
*/

#include <Wire.h>                 // Must include Wire library for I2C
#include <SFE_MicroOLED.h> 
#include "SparkFun_MMA8452Q.h"// Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q
#include "SparkFun_VCNL4040_Arduino_Library.h"

VCNL4040 proximitySensor;
MMA8452Q accel;                   // create instance of the MMA8452 class
#define Serial SerialUSB  

#define PIN_RESET 9                     
#define DC_JUMPER 1                     
MicroOLED oled(PIN_RESET, DC_JUMPER);

void setup() {
  Serial.begin(9600);
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();
  oled.begin();
  oled.clear(ALL);
  oled.display();
  proximitySensor.begin(); //Initialize the sensor

  proximitySensor.powerOffProximity(); //Power down the proximity portion of the sensor
  
  proximitySensor.powerOnAmbient(); //Power up the ambient sensor

  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
}
void textExamples()
{
  //printTitle("Text!", 1);

  // Demonstrate font 0. 5x8 font
  oled.clear(PAGE);     // Clear the screen
  oled.setFontType(0);  // Set font to type 0
  oled.setCursor(0, 0); // Set cursor to top-left
  // There are 255 possible characters in the font 0 type.
  // Lets run through all of them and print them out!
  for (int i=0; i<=255; i++)
  {
    // You can write byte values and they'll be mapped to
    // their ASCII equivalent character.
    oled.write(i);  // Write a byte out as a character
    oled.display(); // Draw on the screen
    delay(10);      // Wait 10ms
    // We can only display 60 font 0 characters at a time.
    // Every 60 characters, pause for a moment. Then clear
    // the page and start over.
    if ((i%60 == 0) && (i != 0))
    {
      delay(500);           // Delay 500 ms
      oled.clear(PAGE);     // Clear the page
      oled.setCursor(0, 0); // Set cursor to top-left
    }
  }}
void loop() {
oled.clear(PAGE);
oled.setFontType(0);  // Set font to type 0
oled.setCursor(0, 0);
oled.print(proximitySensor.getAmbient());
oled.display();
//oled.print(accel.getCalculatedX());
//oled.display();
delay(500);
}
