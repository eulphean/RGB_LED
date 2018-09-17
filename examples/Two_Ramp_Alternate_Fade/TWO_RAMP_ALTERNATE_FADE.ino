/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 08/16/2018
  Description: Use the RAMP library to create a double fade
  sequence for an EXIT sign. 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <RGB_LED.h>
#include <Ramp.h>

// Define LED driver pins.
RGB_LED led1(3, 5, 6);
RGB_LED led2(9, 10, 11);
ramp fadeA;
ramp fadeB; 
const int fadeDuration = 2000; 

void setup() {
  fadeA.go(255, fadeDuration, EXPONENTIAL_IN, FORTHANDBACK);
  fadeB.go(255, fadeDuration, EXPONENTIAL_IN, BACKANDFORTH);
}

void loop() {
  // Set RGB for led1. 
  led1.setColor(fadeA.update(), fadeA.update(), fadeA.update()); 
  led2.setColor(fadeB.update(), fadeB.update(), fadeB.update());
}
