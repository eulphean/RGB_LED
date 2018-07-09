/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 05/06/2018
  Description: In this example, we blink Led1 and fade Led2. 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <RGB_LED.h>

// Define LED driver pins.
RGB_LED led1(3, 5, 6);
RGB_LED led2(9, 10, 11);

enum FadeState { 
  FadeIn, 
  FadeOut
};

// Store last blink and fade times. 
unsigned long lastBlinkTime; 
unsigned long lastFadeTime; 

// Blink & Fade LED states.  
bool ledOn = true; 
FadeState ledFadeState = FadeIn;

int blinkTime = 200; // 1 second - 1000 ms
int fadeInTime = 500;
int fadeOutTime = 500;

void setup() {
  // Record starting time. 
  lastBlinkTime = millis(); 
  lastFadeTime = millis();
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
      led1.setColor(255, 255, 255);
    } else {
      led1.setColor(0, 0, 0);
    }
  } else {
    lastBlinkTime = millis(); // Reset time. 
    ledOn = !ledOn; // Change the ledState. 
  }
}

void fadeLED() {
  unsigned long elapsedTime = millis() - lastFadeTime; 

  // FadeIn state.
  if (ledFadeState == FadeIn) {
    if (elapsedTime > fadeInTime) {
      // Update state. 
      ledFadeState = FadeOut;
      lastFadeTime = millis(); // Reset time. 
    } else {
      // Map the brightness value based on elapsed time. 
      int brightnessVal = map (elapsedTime, 0, fadeInTime, 0, 255); 
      brightnessVal = constrain(brightnessVal, 0, 255);
      led2.setColor(brightnessVal, brightnessVal, brightnessVal); 
    }
  } else if (ledFadeState == FadeOut) {
    if (elapsedTime > fadeOutTime) {
       // Update state to FadeIn. 
       ledFadeState = FadeIn; 
       lastFadeTime = millis(); // Reset time
    } else {
        int brightnessVal = map (elapsedTime, 0, fadeOutTime, 255, 0); 
        brightnessVal = constrain(brightnessVal, 0, 255);
        led2.setColor(brightnessVal, brightnessVal, brightnessVal);
    }
  }
}

