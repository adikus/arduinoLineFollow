/*
 Melody
 
 Plays a melody stored in a string. 
 
 The notes and durations are encoded as follows:

 NOTES:
 c  play "C"
 C  play "#C"
 d  play "D"
 D  play "#D"
 e  play "E"
 f  play "F"
 F  play "#F"
 g  play "G"
 G  play "#G"
 a  play "A"
 A  play "#A"
 b  play "B"
 -  silence

 DURATIONS:
 1  Set as full note
 2  Set as half note
 4  Set as quarter note
 8  Set as eigth note

 SPECIAL NOTATION:
 .  Make the previous note 3/4 the length

 Circuit:
 * Arduino Robot
 
 created 1 May 2013
 by X. Yang
 modified 12 May 2013
 by D. Cuartielles
 
 This example is in the public domain

 This code uses the Squawk sound library designed by STG. For
 more information about it check: http://github.com/stg/squawk
 */

#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>
#include <stdio.h>

int n = -1;

void setup() {
  // initialize the robot
  Robot.begin();

  // initialize the sound library
  Robot.beginSpeaker();
}

void loop() {
  n++;
  Robot.fill(255,255,200);
  char filename[12];
  snprintf(filename, sizeof filename, "santa-%d.bmp", n);
  Robot.drawBMP(filename, 14, 80);
  
  // array containing the melody
  char aTinyMelody[] = "8g--g-f-cggaf--ddgga-f--fefed----a--g---daAag---fefee-f-e-c-e-c--";

  if(n==3){
    n = -1;
  }
  // play the melody
  Robot.playMelody(aTinyMelody);
}
