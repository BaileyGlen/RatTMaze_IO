#include <Servo.h>
struct door
{
  int pinIn;
  int pinOut;
  bool dir; // True = normal
  int minPos;
  int maxPos;
  int curPos;
  bool curState; // 0= Close 1=open
  long nextMoveMs;
  Servo servo;
};
typedef struct door Door;
