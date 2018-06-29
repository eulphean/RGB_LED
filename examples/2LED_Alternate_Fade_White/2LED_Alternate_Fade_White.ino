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
RGB_LED led1(3, 5, 6); 
RGB_LED led2(9, 10, 11);

// Starting FadeState for each LED. 
FadeState led1FadeState = FadeIn;
FadeState led2FadeState = FadeOut;

// Maintain seperate lastTimes for both LEDs. 
unsigned long lastTimeLed1;
unsigned long lastTimeLed2;

// FadeIn and FadeOut times. 
int fadeInTime = 5000;
int fadeOutTime = 5000;

void setup() {
  Serial.begin(9600);
  // Record starting time. 
  lastTimeLed1 = millis(); 
  lastTimeLed2 = millis();
}

void loop() {
  // Calculate the elapsed time for both LEDs. 
  unsigned long int elapsedTimeLed1 = millis() - lastTimeLed1; 
  unsigned long int elapsedTimeLed2 = millis() - lastTimeLed2; 

  // Fade Led1
  fade(led1, led1FadeState, elapsedTimeLed1, lastTimeLed1); 

  // Fade Led2
  fade(led2, led2FadeState, elapsedTimeLed2, lastTimeLed2);
}


void fade(RGB_LED led, FadeState &ledState, unsigned long int &elapsedTime, unsigned long int &lastTime) {
  // FadeIn state.
  if (ledState == FadeIn) {
    if (elapsedTime > fadeInTime) {
      // Update state. 
      ledState = FadeOut;
      lastTime = millis(); // Reset time. 
    } else {
      // Map the brightness value based on elapsed time. 
      int brightnessVal = map (elapsedTime, 0, fadeInTime, 0, 255); 
      brightnessVal = constrain(brightnessVal, 0, 255);
      led.setColor(brightnessVal, brightnessVal, brightnessVal); 
    }
  } else if (ledState == FadeOut) {
    if (elapsedTime > fadeOutTime) {
       // Update state to FadeIn. 
       ledState = FadeIn; 
       lastTime = millis(); // Reset time
    } else {
        int brightnessVal = map (elapsedTime, 0, fadeOutTime, 255, 0); 
        brightnessVal = constrain(brightnessVal, 0, 255);
        led.setColor(brightnessVal, brightnessVal, brightnessVal);
    }
  }
}

