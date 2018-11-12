/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 08/16/2018
  Description: This example creates an array of Ramp variables
  to control 3 different components (R,G,B) for a LED. 
    
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

// LED1 R, G, B components
int led1RGB[3] = {150, 100, 255}; 
// LED2 R, G, B components
int led2RGB[3] = {100, 150, 200}; 

void setup() {
  enableRampA(); 
  enableRampB();
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

