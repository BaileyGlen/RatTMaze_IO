// W. Bailey Glen Jr.
// 03/02/2016
// Arduino 1.6.7
// Arduino Uno Rev 3 

#include <Servo.h>

// Creates a door object for passing data around
struct door
{
  int pinIn;    // pin on the ardion which will receive the door state
  int pinOut;   // pin on the arduino which will drive the door servo
  bool dir;     // True = normal
  int minPos;   // maxiumm close before hitting the wall 
  int maxPos;   // maximum open before hitting the wall
  int curPos;   // current position from 0 to 180
  unsigned long prevMs;  // used for door speed control
  Servo servo;  // generates a servo from servo library
};
// makes "Door = door" ignore this
typedef struct door Door;
