#include <Wire.h>
#include <RGB_LED.h>

// Initialize LEDs. 
RGB_LED led1(9, 10, 11);
RGB_LED led2(3, 5, 6);

// The input buffer.
String buffer;

void setup() {
  // I2C begin.
  Wire.begin();
  // Start our Serial device.
  Serial.begin(9600);
}

void loop() {  
  readSerialData();
  // Send Data over I2C
  sendData();
}

// RGB arrays for 3 LEDs. 
int l1[3]; int l2[3]; int l3[3] = { 50, 50, 50 };

void readSerialData()
{
  // As long as there is serial data available to read, repeat.
  while (Serial.available() > 0)
  {
    // Read the byte.
    char b = Serial.read();

    // End of line character.
    if (b == '\n')
    {
      // Parse out serial data sent from openFrameworks to control
      // the LEDs. The data comes in this format from openFrameworks. 
      // 50,50,50-100,100,100-50,50,50
      
      int firstLedSpacer = buffer.indexOf("-", 0);
      int secondLedSpacer = buffer.indexOf("-", firstLedSpacer+1);

      // The comma positions must be greater than -1.
      if (firstLedSpacer > -1 and secondLedSpacer > -1)
      {
        String led1RGB = buffer.substring(0, firstLedSpacer);
        String led2RGB = buffer.substring(firstLedSpacer + 1, secondLedSpacer);
        String led3RGB = buffer.substring(secondLedSpacer + 1);

        // Split RGB strings at "," and populate RGB led arrays. 
        populateRGBVals(led1RGB, l1);
        led1.setColor(l1[0], l1[1], l1[2]);
                
        populateRGBVals(led2RGB, l2);
        led2.setColor(l2[0], l2[1], l2[2]);

        // For led3, we send the values over I2C.
        populateRGBVals(led3RGB, l3);
      }

      // Clear the buffer.
      buffer = "";
    }
    else
    {
      // If it's not the line feed character, add it to the buffer.
      buffer += b;
    }
  }
}

void populateRGBVals(String ledRGB, int led[]) {
   int firstComma = ledRGB.indexOf(",", 0); 
   int secondComma = ledRGB.indexOf(",", firstComma+1);

   if (firstComma > -1 && secondComma > -1) {
     led[0] = ledRGB.substring(0, firstComma).toInt(); 
     led[1] = ledRGB.substring(firstComma+1, secondComma).toInt();
     led[2] = ledRGB.substring(secondComma+1).toInt(); 
   }
}

void sendData() {
  // Extract the least significant byte from the 16-bit integer value.
  byte rgbData[] = { l3[0] & 255, l3[1] & 255, l3[2] & 255 }; // Prepare a 3 byte array to send over I2C to slave.
  Wire.beginTransmission(8);
  Wire.write(rgbData, 3);
  Wire.endTransmission();
}

void debugPrint() {
    // Print calculated led values. 
  Serial.print(l1[0]);
  Serial.print(",");
  Serial.print(l1[1]);
  Serial.print(",");
  Serial.print(l1[2]);
  Serial.print("-");
  Serial.print(l2[0]);
  Serial.print(",");
  Serial.print(l2[1]);
  Serial.print(",");
  Serial.print(l2[2]);
  Serial.print("-");
  Serial.print(l3[0]);
  Serial.print(",");
  Serial.print(l3[1]);
  Serial.print(",");
  Serial.println(l3[2]);
}

