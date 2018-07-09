/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 05/06/2018
  Description: Fade in and Fade out white. 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <RGB_LED.h>

enum FadeState { 
  FadeIn, 
  FadeOut
};

// Define LED driver pins.
RGB_LED led(3, 5, 6); 
FadeState currentFadeState = FadeIn;

// Record the last time to track the time of the LED. 
unsigned long lastTime; 
int fadeInTime = 1000;
int fadeOutTime = 2000;

void setup() {
  // Record starting time. 
  lastTime = millis(); 
}

void loop() {
  // Calculate the elapsed time. 
  unsigned long int elapsedTime = millis() - lastTime; 

  // FadeIn state. 
  if (currentFadeState == FadeIn) {
     if (elapsedTime > fadeInTime) {
        // Update state to FadeOut.
        currentFadeState = FadeOut;
        lastTime = millis(); // Reset time. 
     } else {
        // Map the brightness value based on elapsed time. 
        int brightnessVal = map (elapsedTime, 0, fadeInTime, 0, 255); 
        brightnessVal = constrain(brightnessVal, 0, 255);
        led.setColor(brightnessVal, brightnessVal, brightnessVal); 
     }
  } else if (currentFadeState == FadeOut) { // FadeOut state.
    if (elapsedTime > fadeOutTime) {
       // Update state to FadeIn. 
       currentFadeState = FadeIn; 
       lastTime = millis(); // Reset time
    } else {
        int brightnessVal = map (elapsedTime, 0, fadeOutTime, 255, 0); 
        brightnessVal = constrain(brightnessVal, 0, 255);
        led.setColor(brightnessVal, brightnessVal, brightnessVal);
    }
  }
}

