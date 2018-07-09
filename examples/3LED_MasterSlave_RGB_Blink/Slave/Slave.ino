// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <RGB_LED.h>

RGB_LED led(3, 5, 6);
byte led_on; 

void setup() {
  Serial.begin(9600);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    led_on = Wire.read(); // receive byte as a character
    Serial.println(led_on);
    update_led();
  }
}

void update_led() {
  if (led_on) {
    led.setColor(0, 0,  50);
  } else {
    led.setColor(0, 0, 0);
  }
}

