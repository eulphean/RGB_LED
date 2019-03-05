#include <Wire.h>
#include <RGB_LED.h>

RGB_LED led1 (9, 10, 11);

// Input buffer.
String buffer; 
int ledVals[3] = { 0, 0, 0 };

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); 
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  readSerialData();

  // Set light color
}

void readSerialData() {
  while (Serial.available() > 0) {
    char b = Serial.read(); 

    // End of line character.
    if (b == '\n')
    {
     // Extract the R,G,B values from the incoming stream. 
     int firstComma = buffer.indexOf(",", 0); 
     int secondComma = buffer.indexOf(",", firstComma+1);
    
     if (firstComma > -1 && secondComma > -1) {
       ledVals[0] = buffer.substring(0, firstComma).toInt(); 
       ledVals[1] = buffer.substring(firstComma+1, secondComma).toInt();
       ledVals[2] = buffer.substring(secondComma+1).toInt(); 
     }  

     led1.setColor(ledVals[0], ledVals[1], ledVals[2]);
     debugPrint();
     
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

void debugPrint() {
   Serial.print(ledVals[0]);
   Serial.print(",");
   Serial.print(ledVals[1]); 
   Serial.print(",");
   Serial.println(ledVals[2]);
}

