/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 05/06/2018
  Description: This example blinks LED1 at the rate of
  blinkTime variable and fades LED2. 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <RGB_LED.h>
#include <Ramp.h>

// Define LED driver pins.
RGB_LED led1(3, 5, 6);
RGB_LED led2(9, 10, 11);

enum FadeState { 
  FadeIn, 
  FadeOut
};
FadeState fadeState = FadeIn;

// Store last blink and fade times. 
unsigned long lastBlinkTime; 

// Blink variables
bool ledOn = true; 
int blinkTime = 200; // 1 second - 1000 ms
int maxBrightnessLed1 = 255; 

// Fade variables
ramp fade;
int fadeInTime = 500;
int fadeOutTime = 1000;
int maxBrightnessLed2 = 255; 

void setup() {
  // Record starting time. 
  lastBlinkTime = millis(); 
  setRamp();
}

void loop() {
  blinkLED(); 
  fadeLED();
}

void blinkLED() {
  unsigned long elapsedTime = millis() - lastBlinkTime; 

  // LED should be white and blinking every *blinkTime seconds*.  
  if (elapsedTime < blinkTime) {
    if (ledOn) {
      led1.setColor(maxBrightnessLed1, maxBrightnessLed1, maxBrightnessLed1);
    } else {
      led1.setColor(0, 0, 0);
    }
  } else {
    lastBlinkTime = millis(); // Reset time. 
    ledOn = !ledOn; // Change the ledState. 
  }
}

void setRamp() {
  if (fadeState == FadeIn) {
    fade.go(/*Digital value to interpolate between (0-255)*/ maxBrightnessLed2, /*Fade duration*/ fadeInTime, 
    /*Interpolation mode*/QUADRATIC_IN, /*Loop mode*/ ONCEFORWARD);
  }
  
  if (fadeState == FadeOut) {
    fade.go(/*Digital value to interpolate between (0-255)*/ 0, /*Fade duration*/ fadeOutTime, 
    /*Interpolation mode*/QUADRATIC_IN, /*Loop mode*/ ONCEFORWARD);
  } 
}

void fadeLED() {
  /* Have reached maximum brightness and current state is FadeIn? */
  if (fade.value() == maxBrightnessLed2 && fadeState == FadeIn) {
    fadeState = FadeOut; 
    setRamp();
  }

  /* Have reached minimum brightness and current state is FadeOut? 
     Update LED state. */
  if (fade.value() == 0 && fadeState == FadeOut) {
    fadeState = FadeIn; 
    setRamp();
  }

  led2.setColor(fade.update(), fade.update(), fade.update());
}

