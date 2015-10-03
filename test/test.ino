/*
 IR array

 Read the analog value of the IR sensors at the
 bottom of the robot. The also-called line following
 sensors are a series of pairs of IR sender/receiver
 used to detect how dark it is underneath the robot.

 The information coming from the sensor array is stored
 into the Robot.IRarray[] and updated using the Robot.updateIR()
 method.

 Circuit:
 * Arduino Robot

 created 1 May 2013
 by X. Yang
 modified 12 May 2013
 by D. Cuartielles

 This example is in the public domain
 */

#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

int lastCompassVal = -1;
int currentCompassVal;

void setup() {
  // initialize the robot
  Robot.begin();
  Robot.beginTFT();
  Robot.stroke(0,0,0);
  Robot.fill(255,200,200);
}

int mini(uint16_t* a){
  int minidx = 0;
  for (int i=1; i<5;i++){
    if (a[i]<a[minidx]){
      minidx = i;
    }
  }
  return minidx;
}

void loop() {
  // store the sensor information into the array
  Robot.updateIR();
  Robot.rect(0, 0, 50, 120); 
  // iterate the array and print the data to the Serial port
//  for (int i = 0; i < 5; i++) {
//    Robot.text((int)Robot.IRarray[i], 20, 20*i);
//  }
  
  //currentCompassVal = Robot.compassRead();
  //Robot.text(currentCompassVal,20,20);
  //Robot.text(lastCompassVal,20,60);
  int mindex = mini(Robot.IRarray);
  Robot.text((int)Robot.IRarray[mindex],20,10);
  Robot.text(mindex,20,20);
  Robot.text(Robot.analogRead(M3),20, 40);
  //Robot.text(mini(Robot.IRarray),30,30);
  if (Robot.IRarray[mindex]<=300 && Robot.IRarray[mindex]>=200){
    if (mindex==2){
      Robot.motorsWrite(75, 75);
      //lastCompassVal = Robot.compassRead();
    }
    else if (mindex==1){
      Robot.motorsStop();
      Robot.motorsWrite(-30, 75);
    }
    else if(mindex==3){
      //Robot.turn(-5);
      Robot.motorsStop();
      Robot.motorsWrite(75, -30);
    }
    else if (mindex=0){
      //Robot.turn(-10);
      Robot.motorsStop();
      Robot.motorsWrite(-50, 75);
    }
    else if (mindex=4){
      Robot.motorsStop();
      Robot.motorsWrite(75, -50);
      //Robot.turn(10);
    }
   else{
     Robot.motorsStop();
   }
  }
 }

