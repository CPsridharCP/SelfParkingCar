#include<Wire.h>
#include<Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include <SoftwareSerial.h>
SoftwareSerial xBee(14, 15); // RX, TX

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *drive_motor = AFMS.getMotor(4);
Adafruit_DCMotor *steering_motor = AFMS.getMotor(1);

String inData;

int y_joystick =0;
int x_joystick =0;

int y_centre = 105;
int x_centre = 111;


void setup(){
  
  Serial.begin(9600);
  xBee.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  AFMS.begin();

}

void loop() 
{
  while (xBee.available() > 0)
    {
       update_joy();
    }

  //255/2 = 127
  // Left Forward <110
  // Right Backward > 140

  if (y_joystick > (y_centre+15)){
    //Move forward
     drive_motor->setSpeed(map(y_joystick,y_centre+15,255,50,100));
     drive_motor->run(FORWARD);
     
  }
  else if (y_joystick < (y_centre-15)){
    //Move Backward
     drive_motor->setSpeed(map(y_joystick,y_centre-15,0,50,100));
     drive_motor->run(BACKWARD);
  }
  else{
    //Stop
     drive_motor->setSpeed(0);
     drive_motor->run(FORWARD);
  }

  if (x_joystick > (x_centre+15)){
    //Move Left
    steering_motor->setSpeed(120);
    steering_motor->run(FORWARD);
  }
  else if (x_joystick < (x_centre-15)){
    //Move Right
    steering_motor->setSpeed(120);
    steering_motor->run(BACKWARD);
  }
  else{
    //Stop
    steering_motor->setSpeed(0);
    steering_motor->run(FORWARD);
  }

  
}

void update_joy(){
 
  char recieved = xBee.read();
        inData += recieved; 

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            //Serial.print("Arduino Received: ");
            //Serial.print(inData);
            x_joystick = inData.substring(0,3).toInt();
            y_joystick = inData.substring(3,6).toInt();
            Serial.println("");
            Serial.println(x_joystick);
            Serial.println(y_joystick);
            Serial.println("");

            inData = ""; // Clear recieved buffer
        }
}


