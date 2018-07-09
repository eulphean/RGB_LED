// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <RGB_LED.h>

enum FadeState { 
  FadeIn, 
  FadeOut
};

FadeState ledState = FadeIn; 
RGB_LED led1(9, 10, 11); 
RGB_LED led2(3, 5, 6);

unsigned long lastTime;
int maxBrightness = 200; // Max value is from 0-255
int minBrightness = 0;

// FadeIn and FadeOut times. 
int fadeInTime = 5000;
int fadeOutTime = 2000;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  lastTime = millis();
}

void loop() {
  // Calculate the elapsed time for both LEDs. 
  unsigned long int elapsedTime = millis() - lastTime; 
  
  // FadeIn state.
  if (ledState == FadeIn) {
    if (elapsedTime > fadeInTime) {
      // Update state. 
      ledState = FadeOut;
      lastTime = millis(); // Reset time. 
    } else {
      // Map the brightness value based on elapsed time. 
      byte brightnessVal = map (elapsedTime, 0, fadeInTime, minBrightness, maxBrightness); 
      brightnessVal = constrain(brightnessVal, minBrightness, maxBrightness);
      setLEDColor(brightnessVal);
    }
  } else if (ledState == FadeOut) {
    if (elapsedTime > fadeOutTime) {
       // Update state to FadeIn. 
       ledState = FadeIn; 
       lastTime = millis(); // Reset time 
    } else {
        byte brightnessVal = map (elapsedTime, 0, fadeOutTime, maxBrightness, minBrightness); 
        brightnessVal = constrain(brightnessVal, minBrightness, maxBrightness);
        setLEDColor(brightnessVal);
    }
  }
}

void sendData(byte brightnessVal) { 
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(brightnessVal); // Send the brightness value on the bus.
  Wire.endTransmission();    // stop transmitting
}

void setLEDColor(byte brightnessVal) {
  // Set the color on all the 3 LEDs. 
  led1.setColor(brightnessVal, 0, 0);
  led2.setColor(0, brightnessVal, 0);
  sendData(brightnessVal);
}

