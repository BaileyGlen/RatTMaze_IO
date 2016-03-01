
#include "pumpDef.h"
#include <Servo.h>
//Servo rightDoorServo;  
//Servo leftDoorServo; 
//Servo homeDoorServo; 

int pos = 0;    // variable to store the servo position

//const int rightDoorIn   = 1;
//const int leftDoorIn    = 2;
//const int homeDoorIn    = 3;
//const int rightDoorOut  = 4;
//const int leftDoorOut   = 5;
//const int homeDoorOut   = 6;

//const int rightPumpIn   = 7;
//const int leftPumpIn    = 8; 
//const int homePumpIn    = 9;
//const int rightPumpOut  = 10;
//const int leftPumpOut   = 11; 
//const int homePumpOut   = 12;
//
//const int rightPumpMinPos = 45;
//const int rightPumpMaxPos = 135;
//const int rightPump
Door rightDoor;
Door leftDoor;
Door homeDoor;

void setup() 
{
  Serial.begin(115200);
//  handshakeNeeded = true;
//  Serial.println ("Initializing port:");
  // mkpump(Input Pin, Output Pin, Direction, minPos, maxPos); 
  Door rightDoor = {1, 4, true, 45, 135, 45,0,0};
  Door leftDoor = {2, 5, true, 45, 135, 45,0,0};
  Door homeDoor = {3, 6, true, 45, 135, 45,0,0};

 
  pinMode(rightDoor.pinIn, INPUT);
  pinMode(leftDoor.pinIn, INPUT);
  pinMode(homeDoor.pinIn, INPUT);
  rightDoor.servo.attach(rightDoor.pinOut);
  leftDoor.servo.attach(leftDoor.pinOut);
  homeDoor.servo.attach(homeDoor.pinOut);

  checkDoor(rightDoor);
  // for tesitng
  pinMode(13,OUTPUT);
//  pinMode(homePumpIn, INPUT);
//  pinMode(rightPumpIn, INPUT);
//  pinMode(leftPumpIn, INPUT);
//  pinMode(homePumpOut, OUTPUT);
//  pinMode(rightPumpOut, OUTPUT);
//  pinMode(leftPumpOut, OUTPUT);
}

void loop() 
{
  checkDoor(rightDoor);
  checkDoor(leftDoor);
  checkDoor(homeDoor);
  //testing
  if (rightDoor.nextMoveMs==0)
  {
    digitalWrite(13,HIGH);
  }else
  {
    digitalWrite(13,LOW);
  }
  
}



void checkDoor(Door &curDoor)
{
  
  if (digitalRead (curDoor.pinIn)==LOW)
  {
    curDoor.curState==false;
    if (curDoor.curPos != curDoor.minPos)
    {
      curDoor.curPos--;
      curDoor.servo.write(curDoor.curPos);
    }
  }
  else 
  {
    curDoor.curState==true;
    if (curDoor.curPos != curDoor.minPos)
    {
      curDoor.curPos++;
      curDoor.servo.write(curDoor.curPos);
    }
  }
  //testing
  if ( ((int)(millis()/1000) % 2)==0)
  {
    curDoor.nextMoveMs=0;
  }
  else 
  {
    curDoor.nextMoveMs=1;
  }
  // check the state of the pump Pin
  // If there is a change in the Pin
}


