
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
Door rightDoor = {2, 5, true, 45, 135, 90,0,0};
Door leftDoor = {3, 6, true, 45, 135, 90,0,0};
Door homeDoor = {4, 7, true, 45, 135, 90,0,0};
void setup() 
{
 Serial.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Hello");
//  handshakeNeeded = true;
//  Serial.println ("Initializing port:");
  // mkpump(Input Pin, Output Pin, Direction, minPos, maxPos); 
//  Door rightDoor = {2, 5, true, 45, 135, 90,0,0,};
//  Door leftDoor = {3, 6, true, 45, 135, 90,0,0};
//  Door homeDoor = {4, 7, true, 45, 135, 90,0,0};
  pinMode(rightDoor.pinIn, INPUT);
  pinMode(leftDoor.pinIn, INPUT);
  pinMode(homeDoor.pinIn, INPUT);
  rightDoor.servo.attach(rightDoor.pinOut);
  leftDoor.servo.attach(leftDoor.pinOut);
  homeDoor.servo.attach(homeDoor.pinOut);
  // for tesitng
  rightDoor.servo.write(rightDoor.curPos);
  leftDoor.servo.write(leftDoor.curPos);
  homeDoor.servo.write(homeDoor.curPos);
}

void loop() 
{  
  checkDoor(rightDoor);
  checkDoor(leftDoor);
  checkDoor(homeDoor);
  //testing

}



void checkDoor(Door &curDoor)
{
  //testing
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
   
    if (curDoor.curPos != curDoor.maxPos)
    {
      curDoor.curPos++;
      curDoor.servo.write(curDoor.curPos);
    }
  }
}


