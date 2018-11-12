/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 08/16/2018
  Description: This example fades a LED from turned off to 
  full White state and back. 
    
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
