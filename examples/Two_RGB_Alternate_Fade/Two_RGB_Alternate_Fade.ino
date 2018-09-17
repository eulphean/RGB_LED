/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 08/16/2018
  Description: Use Ramp library to create a double fade
  sequence for an EXIT sign. Create an array to interpolate
  RGB values. 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <RGB_LED.h>
#include <Ramp.h>

// Define LED driver pins.
RGB_LED led1(3, 5, 6);
RGB_LED led2(9, 10, 11);

// Define ramps for two lights
ramp rampA [3]; // RGB ramp variables
ramp rampB [3]; // RGB ramp variables

// Fade duration.
int duration = 1500;

void setup() {
  Serial.begin(9600);

  // System begins from A->B 
  enableRampA(); 
  enableRampB();

  lastTime = millis();
}

void loop() {
  // Set RGB for led1. 
  led1.setColor(rampA[0].update(), rampA[1].update(), rampA[2].update()); 
  led2.setColor(rampB[0].update(), rampB[1].update(), rampB[2].update());
}

void enableRampA() {
  rampA[0].go(200, duration, QUADRATIC_IN, FORTHANDBACK); // Red
  rampA[1].go(200, duration, QUADRATIC_IN, FORTHANDBACK); // Green
  rampA[2].go(0, duration, QUADRATIC_IN, FORTHANDBACK); // Blue
}

void enableRampB() {
  rampB[0].go(200, duration, CIRCULAR_IN, BACKANDFORTH); // Red
  rampB[1].go(0, duration, CIRCULAR_IN, BACKANDFORTH); // Green
  rampB[2].go(100, duration, CIRCULAR_IN, BACKANDFORTH); // Blue
}

