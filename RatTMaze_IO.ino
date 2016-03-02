
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
/////// Adjust Door Parameters here!!!///////////////////
// For instance, the door ranges are the 4th and 5th parameters below
// The In and Out Pins are the 1st and second parameters below
Door rightDoor = {8,  11, true, 45, 135, 90, millis()};
Door leftDoor  = {9,  12, true, 45, 135, 90, millis()};
Door homeDoor  = {10, 13, true, 45, 135, 90, millis()};

// Declaration of the 3 pump pins here
// We only need to declare inputs for the pumps. The relays
// themselves are the outputs
// The seedstudio relay shield v2.0 uses the following layout
// Digital 4 – controls RELAY4’s COM4 pin (located in J4)
// Digital 5 – controls RELAY3’s COM3 pin (located in J3)
// Digital 6 – controls RELAY2’s COM2 pin (located in J2)
// Digital 7 – controls RELAY1’s COM1 pin (located in J1)
// We are using ...
// rightpump - J4, pin 4
// leftpump  - J3, pin 5
// homepump  - J2, pin 6
int rightPumpPinIn = 4;
int leftPumpPinIn  = 5;
int homePumpPinIn  = 6;

// This variable will be used to handle the delay time
int doorMs = 30; 

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
  // Doors
  pinMode(rightDoor.pinIn, INPUT);
  pinMode(leftDoor.pinIn, INPUT);
  pinMode(homeDoor.pinIn, INPUT);
  // Pumps
  pinMode(rightPumpPinIn, INPUT);
  pinMode(leftPumpPinIn, INPUT);
  pinMode(homePumpPinIn, INPUT);
  
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

  // No need to do anything witht he pumps, its just running through the arduino inputs.
  
}


void checkDoor(Door &curDoor)
{
  // Check if the door is set to be closed...
  if ((digitalRead (curDoor.pinIn)==LOW) && ((unsigned long)(millis() - curDoor.prevMs)  >= doorMs))
  {
    // if it should be closed, but isn't at the closed position...
    if (curDoor.curPos != curDoor.minPos) 
    {
      // ...move towards the close position
      curDoor.curPos = curDoor.curPos - (1*curDoor.dir);
      curDoor.servo.write(curDoor.curPos);
      curDoor.prevMs = millis();
    }
  }

  // same as above, but for when the door should be open
  else 
  {
    if ((curDoor.curPos != curDoor.maxPos) && ((unsigned long)(millis() - curDoor.prevMs)  >= doorMs))
    {
      curDoor.curPos = curDoor.curPos + (1*curDoor.dir);
      curDoor.servo.write(curDoor.curPos);
      curDoor.prevMs = millis();
    }
  }
}


