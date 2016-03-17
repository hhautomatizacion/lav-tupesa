// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
    pinMode(13, OUTPUT);
}

byte x = 0;

void loop()
{
  delay(500);
  digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
  Wire.beginTransmission(39); // transmit to device #4
  //Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  x++;
  delay(1000);
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
}
