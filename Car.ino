char inChar=-1; 
char XinData[3]; 
char YinData[3]; 

bool logX = false;
bool logY = false;

int Xindex;
int Yindex;

String JoyX ="";
String JoyY ="";

int x_joystick = 0;
int y_joystick = 0;

#define OUT

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

void setup(){
  
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() 
{
  OUT getJoystick();
  Serial.println("*********");
  Serial.println(x_joystick);
  Serial.println(y_joystick);
  Serial.println("*********");
  Serial.println("");
   
}

void getJoystick(){
  if (mySerial.available()>0){
    
            inChar = mySerial.read();

            if (logX){
              
              if (inChar != '.'){
                  XinData[Xindex] =inChar;
                  Xindex += 1;
              }
              else
                logX = false;
            }

            if (logY){
              
              if (inChar != '.'){
                YinData[Yindex] =inChar;
                Yindex += 1;  
              }
              else
                logY = false;
            }
            
            if (inChar == 'X'){
              logX = true;
              Xindex = 0;
              
            }
              

            if (inChar == 'Y'){
              logY = true;
              Yindex = 0;
              
            }

        }

        for (int i=0;i<3;i++)
        {
          JoyX += String(XinData[i]);
          JoyY += String(YinData[i]);
        }
    
        x_joystick = JoyX.toInt();
        y_joystick = JoyY.toInt();

        JoyY="";
        JoyX="";
}

