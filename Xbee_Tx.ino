int x,y;
String final_out;

String xOut = "";
String yOut = "";

// Initialising Soft Serial
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() {

  
  // Reading pot values from analig joystick
  x = analogRead(A0);
  y = analogRead(A1);

  // mapping voltage as in range 0-1024 to 0-255
  x= map(x,0,1024,0,255);
  y= map(y,0,1024,0,255);

  // Streing manipulation to maintain a constant 
  // three digit for values from the joystick
  if (x<10){
    xOut="00"+String(x);
  }
  else if (x>=10 && x<100){
    xOut="0"+String(x);
  }
  else{
    xOut=String(x);
  }

  if (y<10){
    yOut="00"+String(y);
  }
  else if (y>=10 && y<100){
    yOut="0"+String(y);
  }
  else{
    yOut=String(y);
  }

  // Concatinating X and Y values from joystck and sending 
  // them through Xbee using the soft serial port
  mySerial.println(xOut+yOut);

  // Comment this line if you are not debugging
  Serial.println(xOut+yOut);
  
  xOut="";
  yOut="";
  mySerial.flush();
  delay(10);
  
}
