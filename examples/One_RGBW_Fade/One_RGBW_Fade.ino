/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 05/06/2018
  Description: Cycle through R,G,B,W colors while fading them 
  in and out. 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <RGB_LED.h>

enum LEDState {
  Red,
  Green,
  Blue, 
  White 
}; 

enum FadeState { 
  FadeIn, 
  FadeOut
};

// Define LED driver pins.
RGB_LED led(3, 5, 6);
LEDState currentLedState = Red; 
FadeState currentFadeState = FadeIn;

// Record the last time to track the time of the LED. 
unsigned long lastTime; 

// Current LED state. 
bool ledOn = true; 
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
        setLEDColor(brightnessVal);
     }
  } else if (currentFadeState == FadeOut) { // FadeOut state.
    if (elapsedTime > fadeOutTime) {
       // Update state to FadeIn. 
       currentFadeState = FadeIn; 
       lastTime = millis(); // Reset time
       updateLEDState();
    } else {
        int brightnessVal = map (elapsedTime, 0, fadeOutTime, 255, 0); 
        brightnessVal = constrain(brightnessVal, 0, 255);
        setLEDColor(brightnessVal);
    }
  }
}

// Set the LED color based on the current LED state.
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

// Cycle through different LEDs to turn on. 
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

