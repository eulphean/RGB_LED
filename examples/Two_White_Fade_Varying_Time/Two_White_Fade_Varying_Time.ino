/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 08/16/2018
  Description: Use multiple RAMPs to create varying fades. 
  Look fade documentation at https://github.com/siteswapjuggler/RAMP
  to try multiple interpolation modes and loop modes. 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Include RGB_LED and Ramp library.
#include <RGB_LED.h>
#include <Ramp.h>

// Define LED driver pins.
RGB_LED led1(3, 5, 6);
RGB_LED led2(9, 10, 11);

// Define ramps for two lights.
ramp fadeA; 
int maxBrightnessA = 255; // Max brightness to fade till for A

ramp fadeB;
int maxBrightnessB = 150; // Max brightness to fade till for B

// Fade duration (In & Out)
int fadeTimesA[2] = { 1000, 2000 }; // FadeIn = fadeTimesA[0] = 1000, FadeOut = fadeTimes[1] = 2000
int fadeTimesB[2] = { 500, 200 }; // FadeIn = fadeTimesB[0] = 500, FadeOut = fadeTimes[1] = 200

enum FadeState {
  FadeIn,
  FadeOut
};

// Initial fade state for LED1
FadeState stateLED1 = FadeIn; 

// Initial fade state for LED2
FadeState stateLED2 = FadeOut;

void setup() {
  Serial.begin(9600);

  setRampA();
  setRampB();
}

void loop() {
  /*State change triggers. 
    Have reached maximum brightness and current state is FadeIn? 
    Have reached minimum brightness and current state is FadeOut?
  */
  if (fadeA.value() == maxBrightnessA && stateLED1 == FadeIn) {
     stateLED1 = FadeOut;
     setRampA(); 
  }

  if (fadeA.value() == 0 && stateLED1 == FadeOut) {
     stateLED1 = FadeIn; 
     setRampA();
  }

   /*State change triggers. 
    Have reached maximum brightness and current state is FadeIn? 
    Have reached minimum brightness and current state is FadeOut?
  */
  led1.setColor(fadeA.update(), fadeA.update(), fadeA.update()); 

  if (fadeB.value() == maxBrightnessB && stateLED2 == FadeIn) {
     stateLED2 = FadeOut;
     setRampB(); 
  }

  if (fadeB.value() == 0 && stateLED2 == FadeOut) {
     stateLED2 = FadeIn; 
     setRampB();
  }
  led2.setColor(fadeB.update(), fadeB.update(), fadeB.update());
}

void setRampA() {
  if (stateLED1 == FadeIn) {
    fadeA.go(/*Digital value to interpolate between (0-255)*/ maxBrightnessA, /*Fade duration*/ fadeTimesA[0], 
    /*Interpolation mode*/QUADRATIC_IN, /*Loop mode*/ ONCEFORWARD);
  }
  
  if (stateLED1 == FadeOut) {
    fadeA.go(/*Digital value to interpolate between (0-255)*/ 0, /*Fade duration*/ fadeTimesB[1], 
    /*Interpolation mode*/QUADRATIC_IN, /*Loop mode*/ ONCEFORWARD);
  }  
}

void setRampB() {
  if (stateLED2 == FadeIn) {
    fadeB.go(/*Digital value to interpolate between (0-255)*/ maxBrightnessB, /*Fade duration*/ fadeTimesB[0], 
    /*Interpolation mode*/QUADRATIC_IN, /*Loop mode*/ ONCEFORWARD);
  }
  
  if (stateLED2 == FadeOut) {
    fadeB.go(/*Digital value to interpolate between (0-255)*/ 0, /*Fade duration*/ fadeTimesB[1], 
    /*Interpolation mode*/QUADRATIC_IN, /*Loop mode*/ ONCEFORWARD);
  }  
}

