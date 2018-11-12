/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *

  Author: Amay Kataria
  Date: 05/06/2018
  Description: The example blinks an LED at blinkTime rate. 
  The color of the LED is generated randomly in
  generateRandomColor(). 
    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <RGB_LED.h>

// Define LED driver pins.
RGB_LED led1(3, 5, 6);
RGB_LED led2(9, 10, 11);

// Store new colors in this array.  
int color1 [3];
int color2 [3];

// Record the last time to track the time of the LED. 
unsigned long lastTime; 

// Current LED state. 
bool ledOn = true; 

// By decreasing this number, you can make the led blink faster. 
// This is the time it's ON and then OFF. 
int blinkTime = 1000; // 1 second - 1000 ms

void setup() {
  // Record starting time. 
  lastTime = millis(); 

  // Generate random colors for LEDs.
  generateRandomColor(color1);
  generateRandomColor(color2);
}

void loop() {
  unsigned long currentTime = millis(); 

  // LED should be white and blinking every *blinkTime seconds*.  
  if (currentTime - lastTime < blinkTime) {
    if (ledOn) {
      led1.setColor(color1[0], color1[1], color1[2]);
      led2.setColor(color2[0], color2[1], color2[2]);
    } else {
      led1.setColor(0, 0, 0);
      led2.setColor(0, 0, 0);
    }
  } else {
    lastTime = millis(); // Reset time. 
    ledOn = !ledOn; // Change the ledState. 
    
    // Generate random colors for LEDs next time the 
    // LED is turning on.  
    if (ledOn) {
      generateRandomColor(color1); 
      generateRandomColor(color2);
    }
  }
}

void generateRandomColor(int color []) {
  // Generate new random colors for the LEDs. 
  for (int i = 0; i < 3; i++) {
    color[i] = random(0, 256); // Max value is exclusive. 
  }
}
