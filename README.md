# RatTMaze_IO
###This is the arduino script which receives from the miniIO to drive the doors and pumps.
**The Files required to install ethovision are available on box**
##Installation Process
###Ethovision
1. Install 'Eth_8.5.614.exe'
2. Install 'P.ET085.614.01 Hotfix for ATC Random.exe'
3. Install 'SetupHardwareInterface_MiniIobox 2.0.6'
4. Download the 'TMazeIO_Template' and place in your ethovision folder

###Arduino
1. Download the latest version of arduino from the internet and install it
2. Download 'TMazeIO.ino'
3. Plug the arduino into the usb port. 
4. Select the correct port in the arduino software
5. Build and upload the ino

## Setup Hardware
1. Camera with drivers installed
2. Noldus mini USB-IO box connect to 24V power supply and USB
3. Connect 4 ethernet cables to TTL. 
  * First 2 connect to arduino steppers to drive pumps
  * Second 2 commect to arduino input pins
4. Give arduino power (usb or power plug)
5. Plug in output cables to doors.

##Setup Experiment
1. Create a new _template_ experiment
2. Select the downloaded TMazeIO_Template
3. Name the new experiment and decide where it will be saved
4. Under Experiment Explorer
  * Video Source 
   * Select 'Live Tacking'
  *Trial Control Hardware
   * Check 'Use of Trial Control hardware'
   * Click 'Settings'
    1.Select mini USB-IO box from dropdown list
    2.set up the first four TTLS 
  * Set up Arena Settings and Detection Settings

##Run Experiment
1. Select appropriate Arena and Detection
2. Set the trial control settings
  * update email/text
  * set delay
  * **if this is a change to a perviously used trial control, duplicate and make the change**
3. Acquire Data

## Documentation
###Hardware
[RelayShield](http://www.seeedstudio.com/wiki/Relay_Shield_V2.0 "Relay Shield V2.0 from Seed Studio")

[Arduino](https://www.arduino.cc/en/Main/ArduinoBoardUno "Arduino Uno")

[Ethovision](http://www.noldus.com/restricted/ethovision-xt-8 "Ethovision XT 8.5"): This may be taken down, requires login

#To Do:
###Ethovision
* ~~Basic Trial Control~~
* Tracking
* Maze Setup

###Arduino
 INO 
 * Pump Code
  * Functioning
  * Commented
 * Door Code
  * ~~Functioning~~
  * Tuned
  * Commented
 H
 * ~~Functioning~~
 * Commented

###Hardware
* Functional wiring
 * Doors
 * Pumps
 * IO/Box
 * Labels on Arduino
* Set up camera
* Keyboard
* Mouse
* Monitor

###Documentation
