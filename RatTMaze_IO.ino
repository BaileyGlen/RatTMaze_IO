

#include <Servo.h>
Servo rightDoor;  
Servo leftDoor; 
Servo homeDoor; 

int pos = 0;    // variable to store the servo position

const int rightDoorIn   = 1;
const int leftDoorIn    = 2;
const int homeDoorIn    = 3;
const int rightDoorOut  = 4;
const int leftDoorOut   = 5;
const int homeDoorOut   = 6;

const int rightPumpIn   = 7;
const int leftPumpIn    = 8; 
const int homePumpIn    = 9;
const int rightPumpOut  = 10;
const int leftPumpOut   = 11; 
const int homePumpOut   = 12;
//
//const int syncPIN       = 2;
//bool handshakeNeeded;
//const unsigned long timeOutMin   = 500000;

void setup() 
{
  Serial.begin(115200);
//  handshakeNeeded = true;
//  Serial.println ("Initializing port:");
  
  pinMode(rightDoorIn, INPUT);
  pinMode(leftDoorIn, INPUT);
  pinMode(homeDoorIn, INPUT);
  myservo.attach(rightDoorOut);
  myservo.attach(leftDoorOut);
  myservo.attach(homeDoorOut);
  
  pinMode(homePumpIn, INPUT);
  pinMode(rightPumpIn, INPUT);
  pinMode(leftPumpIn, INPUT);
  pinMode(homePumpOut, OUTPUT);
  pinMode(rightPumpOut, OUTPUT);
  pinMode(leftPumpOut, OUTPUT);
}


/////////////////////////////////
// consider \n at the end of messages...for easier formatting
/////////////////////////
void loop() 
{
  if (handshakeNeeded)
  { 
    delay(100);

    while (Serial.available())
    {
      Serial.read();
    }
    Serial.print("AAA\n"); 
    handshakeNeeded = false;   
  }
  else  
  {  
    if (Serial.available())
    {
  //    Serial.println(micros());
  //    Serial.println ("Reading Data:");
      boolean output = false;
      char message[4]; // should be 5
      char errorMessage = readData(message); //0 for no error, 1 or more for errors
      if (errorMessage == '0') // if readData() doesn't fail (ie. returns 1 instead of 0)
      {
  //      Serial.println("The size of the message is: " + String(strlen(message)));
        
        char messageType  = message[0];
        char pinNumber    = message[1]; //- '0'; //if hardware, if not - 0
        char pinState     = message[2]; //- '0'; // this is taking the asci value and subtracting the ascii value of 0 from it.; // if hardware, if not - 0
        char endLine      = message[3];
  
        
  //    Serial.print ((int)(message[3]-'0'));
  //    Serial.println(message[0],DEC);
  //    Serial.print ((int)(message[4]-'0'));
  //    Serial.print ('\n');
  //      Serial.print (message);
        if (endLine == '\n')
        {
          switch (messageType)
          {
          case deviceCMD:
            pinNumber = pinNumber - '0';
            if (pinNumber == homeDoorPIN || pinNumber == rightDoorPIN  || pinNumber == leftDoorPIN || pinNumber == homePumpPIN || 
              pinNumber == rightPumpPIN || pinNumber == leftPumpPIN || pinNumber == syncPIN) // if readData() doesn't fail (ie. returns 1 instead of 0)
            {
              pinState = pinState - '0';
              if (pinState == 0 || pinState == 1)
              {
                if (pinNumber == 0) {pinNumber = 10;} // turn 0 into 10 
    //          Serial.println("Current Device State: " + String(pinState));
                digitalWrite(pinNumber, pinState); // Set Device State 
                errorMessage = '0';
              } 
              else 
              {
                errorMessage = '3';// Incorrect Device State Errorm
              }
            }
            else 
            {
              errorMessage = '2'; //Incorrect PIN Error   
            }  
            break;
          case syncCMD:
            errorMessage = '0';
            output = true;
            break;
          case handshakeCMD:
            errorMessage = '0';
            break;
          default:
  //          Serial.print("wth");
            errorMessage = '1'; // Incorrect CMD Error
          }
        }
        else 
        {
          errorMessage = '4'; //Incorrect endline 
        } 
      }
      else 
      {
         errorMessage = '5'; // TimeOut Error
      }
      printConfirmation(errorMessage,message, output);
    }  
  }
}

char readData(char message[])
{
  boolean timeOut = false;
  unsigned long startTime = micros();
  unsigned long delayTime = 0;
  while ((Serial.available() <= 3) && (timeOut == false))
  {
    unsigned long currentTime = micros();
    if(currentTime >= startTime)
    {
      delayTime = currentTime - startTime;
      if (delayTime >= timeOutMin)
      {
//        Serial.println(delayTime);
        timeOut = true;
      }
    }
    else 
    {
      startTime = currentTime;
    }
  }
  if (timeOut == false)
  {
    message[0] = Serial.read();
    message[1] = Serial.read();
    message[2] = Serial.read();
    message[3] = Serial.read();
//    Serial.println("reading"); 
    return '0';
  }
  else if (timeOut == true);
  {
//    Serial.print("1"); // TimeOut Error
    while (Serial.available())
    {
      Serial.read();  
    }
//    Serial.println ("here I am!");
    return '5';  //Timed Out
  }
}
    
//  Serial.println("The size of the message is: " + String(strlen(message)));
//wth did all the timeout code go?????????????


void printOutput()
{
  Serial.print ((digitalRead(syncPIN)));
  Serial.print ((digitalRead(homePumpPIN)));
  Serial.print ((digitalRead(rightPumpPIN)));
  Serial.print ((digitalRead(leftPumpPIN)));
  Serial.print ((digitalRead(homeDoorPIN)));
  Serial.print ((digitalRead(rightDoorPIN)));
  Serial.print ((digitalRead(leftDoorPIN+10)));
  Serial.print ('\n');
  
  
// Serial.print("Pump:  Door:\n H R L     H R L\n"); 
// Serial.print(" " + String(digitalRead(homePumpPIN)) + String(" ") + String(digitalRead(rightPumpPIN)) + String(" ") + String(digitalRead(leftPumpPIN)) + String("     ") + String(digitalRead(homeDoorPIN)) + 
// String(" ") + String(digitalRead(rightDoorPIN)) + String(" ") + String(digitalRead(leftDoorPIN)) + "\n");
// // + " " + (char)digitalRead(rightPumpPIN) + " " + (char)digitalRead(leftPumpPIN) + "     " + (char)digitalRead(homeDoorPIN) + " " + (char)digitalRead(rightDoorPIN) + " " + (char)digitalRead(leftDoorPIN) + "\n"
}

void printConfirmation(char errorMessage, char message[],boolean output)
{
  if (errorMessage == '0')
  {
    Serial.print(message[0]);
    Serial.print(message[1]);
    Serial.print(message[2]);
    Serial.print('\n');
  }
  else
  {
    Serial.print (errorCMD);
    Serial.print (errorMessage);
    Serial.print ('\n');

  }
  if (output==true)
  {
    printOutput();
  }   
}


