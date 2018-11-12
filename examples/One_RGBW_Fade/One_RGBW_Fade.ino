/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 05/06/2018, Updated 11/11/2018
  Description: Cycle through R,G,B,W colors while fading them 
  in and out. 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <RGB_LED.h>
#include <Ramp.h>

// LED colors
enum LEDState {
  Red,
  Green,
  Blue, 
  White 
}; 
LEDState currentLedState = Red; 

// LED fade state
enum FadeState { 
  FadeIn, 
  FadeOut
};
FadeState fadeState = FadeIn;

// LED driver pins
RGB_LED led(3, 5, 6);

// Fade variables
ramp fade; 
int fadeInTime = 1000;
int fadeOutTime = 2000;
int maxBrightness = 255; 

void setup() {
  // Initialize ramp.
  setRamp();
}

void loop() {
  /* Have reached maximum brightness and current state is FadeIn? */
  if (fade.value() == maxBrightness && fadeState == FadeIn) {
    fadeState = FadeOut; 
    setRamp();
  }

  /* Have reached minimum brightness and current state is FadeOut? 
     Update LED state. */
  if (fade.value() == 0 && fadeState == FadeOut) {
    updateLEDState();
    fadeState = FadeIn; 
    setRamp();
  }

  setLEDColor(fade.update());
}


void setRamp() {
  if (fadeState == FadeIn) {
    fade.go(/*Digital value to interpolate between (0-255)*/ maxBrightness, /*Fade duration*/ fadeInTime, 
    /*Interpolation mode*/QUADRATIC_IN, /*Loop mode*/ ONCEFORWARD);
  }
  
  if (fadeState == FadeOut) {
    fade.go(/*Digital value to interpolate between (0-255)*/ 0, /*Fade duration*/ fadeOutTime, 
    /*Interpolation mode*/QUADRATIC_IN, /*Loop mode*/ ONCEFORWARD);
  } 
}

// Set LED colors.
void setLEDColor(int brightnessVal) {
  switch (currentLedState) {
    case Red: {
       led.setColor(brightnessVal, 0, 0);
       break;
    }

    case Green: {
      led.setColor(0, brightnessVal, 0);
      break;
    }

    case Blue: {
      led.setColor(0, 0, brightnessVal); 
      break;
    }

    case White: {
      led.setColor(brightnessVal, brightnessVal, brightnessVal);
      break;
    }

    default: {
      break;
    }
  }
}

// Cycle LED state. 
void updateLEDState() {
  if (currentLedState == Red) {
     currentLedState = Green; 
  } else if (currentLedState == Green) {
    currentLedState = Blue;
  } else if (currentLedState == Blue) {
    currentLedState = White; 
  } else if (currentLedState == White) {
    currentLedState = Red; 
  }
}

