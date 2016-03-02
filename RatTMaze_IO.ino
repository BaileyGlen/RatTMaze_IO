
// W. Bailey Glen Jr.
// 03/02/2016
// Arduino 1.6.7
// Arduino Uno Rev 3 

// Included code in the servo library and the 
// definition for the Door Struct

#include "doorDef.h"  // built into arduino
#include <Servo.h>    

// Declaration and Initiation of 3 Doors. Here, adjustments
// can be made to the pins, default doors states, etc
Door rightDoor = {8,  11, true, 45, 135, 90,0,0};
Door leftDoor  = {9,  12, true, 45, 135, 90,0,0};
Door homeDoor  = {10, 13, true, 45, 135, 90,0,0};


void setup() 
{
  // The serial code below can be incommented to allow Serial reporting for erroring
  // using Serial.println ("desired text here");
  // Serial.begin(115200);
  // while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  // }
  //  Serial.println("Hello");


  // Set Input and output pins for pumps and doors
  pinMode(rightDoor.pinIn, INPUT);
  pinMode(leftDoor.pinIn, INPUT);
  pinMode(homeDoor.pinIn, INPUT);

  //Attach the servos to the door pin outpus
  rightDoor.servo.attach(rightDoor.pinOut);
  leftDoor.servo.attach(leftDoor.pinOut);
  homeDoor.servo.attach(homeDoor.pinOut);
  
  //Set the position of the doors
  rightDoor.servo.write(rightDoor.curPos);
  leftDoor.servo.write(leftDoor.curPos);
  homeDoor.servo.write(homeDoor.curPos);
}

void loop() 
{  
  // check the position of each door and update its positions
  checkDoor(rightDoor);
  checkDoor(leftDoor);
  checkDoor(homeDoor);
}


void checkDoor(Door &curDoor)
{
  // Check if the door is set to be closed...
  if (digitalRead (curDoor.pinIn)==LOW)
  {
    // if it should be closed, but isn't at the closed position...
    if (curDoor.curPos != curDoor.minPos)
    {
      // ...move towards the close position
      curDoor.curPos--;
      curDoor.servo.write(curDoor.curPos);
    }
  }

  // same as above, but for when the door should be open
  else 
  {
    if (curDoor.curPos != curDoor.maxPos)
    {
      curDoor.curPos++;
      curDoor.servo.write(curDoor.curPos);
    }
  }
}


