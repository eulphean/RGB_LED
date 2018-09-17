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
ramp fade;
const int fadeDuration = 2000; 

void setup() {
  fade.go(255, fadeDuration, EXPONENTIAL_IN, FORTHANDBACK);
}

void loop() {
  // Set RGB for led1. 
  led1.setColor(fade.update(), fade.update(), fade.update()); 
}
