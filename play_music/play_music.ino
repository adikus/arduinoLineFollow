#include <ArduinoRobot.h>

void setup(){
  Robot.begin();
  Robot.beginSpeaker();//Initialize the sound module
  Robot.beginSD();//Initialize the sd card
  Robot.playFile("melody.sqm");//Play the original music come with the robot.
}

void loop(){
  //do other stuff here
}
