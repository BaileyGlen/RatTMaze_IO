
#include "pumpDef.h"
#include <Servo.h>

Door rightDoor = {2, 5, true, 45, 135, 90,0,0};
Door leftDoor = {3, 6, true, 45, 135, 90,0,0};
Door homeDoor = {4, 7, true, 45, 135, 90,0,0};
void setup() 
{
// Serial.begin(115200);
//   while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }
//  Serial.println("Hello");

  pinMode(rightDoor.pinIn, INPUT);
  pinMode(leftDoor.pinIn, INPUT);
  pinMode(homeDoor.pinIn, INPUT);
  rightDoor.servo.attach(rightDoor.pinOut);
  leftDoor.servo.attach(leftDoor.pinOut);
  homeDoor.servo.attach(homeDoor.pinOut);
  rightDoor.servo.write(rightDoor.curPos);
  leftDoor.servo.write(leftDoor.curPos);
  homeDoor.servo.write(homeDoor.curPos);
}

void loop() 
{  
  checkDoor(rightDoor);
  checkDoor(leftDoor);
  checkDoor(homeDoor);
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


