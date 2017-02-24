int x,y;
String final_out;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  
  //Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() {
  
  x = analogRead(A0);
  y = analogRead(A1);
  x= map(x,0,1024,0,255);
  y= map(y,0,1024,0,255);
  
  mySerial.print(String("X"+String(x)+"."));
  mySerial.println(String("Y"+String(y)+"."));
  delay(500);
  
}
