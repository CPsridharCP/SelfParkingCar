int x,y;
String final_out;

String xOut = "";
String yOut = "";

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() {

  
  
  x = analogRead(A0);
  y = analogRead(A1);
  x= map(x,0,1024,0,255);
  y= map(y,0,1024,0,255);


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

  
  //mySerial.print(String("X"+xOut+"."));
  //mySerial.println(String("Y"+yOut+"."));
  mySerial.println(xOut+yOut);
  //Serial.print(String("X"+xOut+"."));
  //Serial.println(String("Y"+yOut+"."));


 
  
  //delay(100);
  xOut="";
  yOut="";
  mySerial.flush();
  delay(10);
  
}
