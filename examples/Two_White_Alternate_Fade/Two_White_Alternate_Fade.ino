/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 08/16/2018
  Description: Use multiple RAMPs to create varying fades. 
  Look fade documentation at https://github.com/siteswapjuggler/RAMP
  to try multiple interpolation modes and loop modes. Both
  the LEDs fade at different times, which are set by
  controlling durationA and durationB variables. 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Include RGB_LED and Ramp library.
#include <RGB_LED.h>
#include <Ramp.h>

// Define LED driver pins.
RGB_LED led1(3, 5, 6);
RGB_LED led2(9, 10, 11);

// Define ramps for two lights
ramp fadeA; 
ramp fadeB;

// Fade duration for both the lights.
int durationA = 1000; // 1 second
int durationB = 2000; // 2 second

void setup() {
  Serial.begin(9600);

  // System begins from A->B 
  enableRampA(); 
  enableRampB();
}

void loop() {
  led1.setColor(fadeA.update(), fadeA.update(), fadeA.update()); 
  led2.setColor(fadeB.update(), fadeB.update(), fadeB.update());
}

void enableRampA() {
  fadeA.go(/*Digital value to interpolate between (0-255)*/ 255, /*Fade duration*/ durationA, 
  /*Interpolation mode*/QUADRATIC_IN, /*Loop mode*/ FORTHANDBACK);
}

void enableRampB() {
  fadeB.go(/*Digital value to interpolate between (0-255)*/ 255, /*Fade duration*/ durationB, 
  /*Interpolation mode*/QUADRATIC_IN, /*Loop mode*/ BACKANDFORTH);
}

