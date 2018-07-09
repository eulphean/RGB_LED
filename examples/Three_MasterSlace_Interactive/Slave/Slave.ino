#include <Wire.h>
#include <RGB_LED.h>

RGB_LED led(3, 5, 6);
byte ledRGB[3] = { 50, 50, 50 };

void setup() {
  Serial.begin(9600);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
  led.setColor(ledRGB[0], ledRGB[1], ledRGB[2]);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  int curIdx = 0;
  while (Wire.available() > 0 && curIdx < 3) { // loop through all but the last
    ledRGB[curIdx] = Wire.read(); // Read byte off the bus.
    curIdx++;
  }
}

