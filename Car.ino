String inData;
String JoyX ="";
String JoyY ="";

#include <SoftwareSerial.h>
SoftwareSerial xBee(14, 15); // RX, TX

void setup() {
    Serial.begin(9600);
    Serial.println("Waiting for Raspberry Pi to send a signal...\n");
    xBee.begin(9600);
}

void loop() {
    
    while (xBee.available() > 0)
    {
       update_joy();
    }
    Serial.println("");
    Serial.println(JoyX);
    Serial.println(JoyY);
    Serial.println("");
    
}

void update_joy(){
 
  char recieved = xBee.read();
        inData += recieved; 

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            //Serial.print("Arduino Received: ");
            //Serial.print(inData);
            JoyX = inData.substring(0,3);
            JoyY = inData.substring(3,6);

            inData = ""; // Clear recieved buffer
        }
}

