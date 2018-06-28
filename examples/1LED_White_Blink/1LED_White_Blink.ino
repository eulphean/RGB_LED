/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 05/06/2018
  Description: This example lets you blink an LED at a specific 
  rate. The color of the LED is white. You can change the color
  of the LED by changing the RGB value, which is set. 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <RGB_LED.h>

// Define LED driver pins.
RGB_LED led(3, 5, 6);

// Record the last time to track the time of the LED. 
unsigned long lastTime; 

// Current LED state. 
bool ledOn = true; 

// By decreasing this number, you can make the led blink faster. 
// This is the time it's ON and then OFF. 
int blinkTime = 2000; // 1 second - 1000 ms

void setup() {
  // Record starting time. 
  lastTime = millis(); 
}

void loop() {
  unsigned long currentTime = millis(); 

  // LED should be white and blinking every *blinkTime seconds*.  
  if (currentTime - lastTime < blinkTime) {
    if (ledOn) {
      led.setColor(255, 255, 255);
    } else {
      led.setColor(0, 0, 0);
    }
  } else {
    lastTime = millis(); // Reset time. 
    ledOn = !ledOn; // Change the ledState. 
  }
}

