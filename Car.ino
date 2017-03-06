#include<Wire.h>
#include<Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Attaching soft serial
#include <SoftwareSerial.h>
SoftwareSerial xBee(14, 15); // RX, TX

// Attaching Steering and Drive mototrs to library objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *drive_motor = AFMS.getMotor(4);
Adafruit_DCMotor *steering_motor = AFMS.getMotor(1);

String inData;
long duration,  cm;

int y_joystick =0;
int x_joystick =0;

//int y_centre = 105;
//int x_centre = 111;
int y_centre = 134;
int x_centre = 128;

String xOut = "";

int distance = 0;
int car_speed = 0;
const byte interruptPin_one = 2;
const byte interruptPin_two = 3;

bool drive = true;
const int pingPin = 10;

void setup(){
  
  Serial.begin(9600);
  Serial.println("restart");
  xBee.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  AFMS.begin();

  
  // Uncomment these to enable interrupt based control
  //Two pins go high when obstracle is less than 100 cm
  //Two pins go low when obstracle is greater than 100 cm
  //attachInterrupt(digitalPinToInterrupt(interruptPin_one), autonomous_mode, RISING);
  //attachInterrupt(digitalPinToInterrupt(interruptPin_two), drive_mode, FALLING);

}

void loop() 
{
  // Check XBee for joystick contol and update x_joystick and y_joystick variables
  while (xBee.available() > 0)
    {
      update_joy();
    }

  // Pull distance to obstacle from PING and update cm variable
  call_distance();

  // Modify Speed function proportionally reduces the speed of the car
  // to the proximity measured from PING
  if (cm < 90){
    modify_speed();
    //drive_car();
  }

    // Drive car actuates the motors based on the decisions taken above
    drive_car();

}


void modify_speed(){

      // Proportionl control to reduce speed
      if (cm > 30 ){
        y_joystick = y_joystick - (map(y_joystick,y_centre,250,0,10)*y_joystick/10);
      }
      else{
        // If too close to object revese is triggerd
        y_joystick = 0;
      }
}

void drive_car(){
  
  //255/2 = 127
  // Left Forward <110
  // Right Backward > 140

  if (y_joystick > (y_centre+15)){
    //Move forward
     drive_motor->setSpeed(map(y_joystick,y_centre+10,255,50,80));
     drive_motor->run(FORWARD);
     
  }
  else if (y_joystick < (y_centre-15)){
    //Move Backward
     drive_motor->setSpeed(map(y_joystick,y_centre-10,0,50,80));
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
        // First three chracters correspond to X and
        // Last three characters correspond to Y joystick
        if (recieved == '\n')
        {
            //Serial.print("Arduino Received: ");
            //Serial.print(inData);
            x_joystick = inData.substring(0,3).toInt();
            y_joystick = inData.substring(3,6).toInt();
            //Serial.println("");
            //Serial.println(x_joystick);
            //Serial.println(y_joystick);
            //Serial.println("");
            inData = ""; // Clear recieved buffer
        }
}

void call_distance(){

  // Mesures proximity and updates distcne in cm to cm vaiable
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);


  //Serial.println(cm);
  
  //Serial.print("cm");
 
  //LIMITING to 250 cm max
  if (cm>250){
    cm = 250;
  }
  else{
  }

  if (cm<10){
    xOut="00"+String(cm);
  }
  else if (cm>=10 && cm<100){
    xOut="0"+String(cm);
  }
  else{
    xOut=String(cm);
  }
  //Serial.println(cm);
  Serial.println(xOut);
  Serial.flush();
  delay(30);
  
}

long microsecondsToCentimeters(long microseconds) {
  
  return microseconds / 29 / 2;
}


