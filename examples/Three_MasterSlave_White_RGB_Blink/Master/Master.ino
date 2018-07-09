#include <Wire.h>
#include <RGB_LED.h>

RGB_LED led1(9, 10, 11); 
RGB_LED led2(3, 5, 6);

unsigned long lastTime;
unsigned long blinkTime = 500;
byte led_on = 0; // 0 or 1 to determine the LED state. 


void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  lastTime = millis();
}

void loop() {
  unsigned long currentTime = millis(); 

  // LED should be white and blinking every *blinkTime seconds*.  
  if (currentTime - lastTime < blinkTime) {
    if (led_on) {
        led1.setColor(50, 50, 50);
        led2.setColor(50, 50, 50); 
        sendData(); // For the third LED, send data on serial bus. 
    } else {
        led1.setColor(0, 0, 0);
        led2.setColor(0, 0, 0);
        sendData();
    }
  } else {
    lastTime = millis(); // Reset time. 
    led_on = !led_on; // Change the ledState. 
  }

  delay(100);
}

void sendData() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(led_on);        // send 3rd led state on wire. 
  Wire.endTransmission();    // stop transmitting
}
