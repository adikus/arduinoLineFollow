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

int n = 0;
int lastLeftMotor = -1;
int lastRightMotor = -1;

void loop() {
  n = n + 1;
  // store the sensor information into the array
  Robot.updateIR();
  if (n%10==0){
    Robot.rect(0, 0, 80, 120); 
  }
  // iterate the array and print the data to the Serial port
//  for (int i = 0; i < 5; i++) {
//    Robot.text((int)Robot.IRarray[i], 20, 20*i);
//  }
  
  int mindex = mini(Robot.IRarray);
  if (n%10==0){
    Robot.text((int)Robot.IRarray[mindex],20,10);
    Robot.text(mindex,20,20);
  }
  //Robot.text(Robot.analogRead(M3),20, 40);

  if (Robot.IRarray[mindex]<=450){
    if (mindex==2){
      if (n%10==0){
        Robot.text("Middle", 10, 50);
      }
      Robot.motorsWrite(75, 75);
      
      lastLeftMotor = 75;
      lastRightMotor = 75;
    }
    else if (mindex==1){
      if (n%10==0){
        Robot.text("Right", 10, 50);
      }
     // Robot.motorsStop();
      //Robot.motorsWrite(-45, 85);
      Robot.motorsWrite(85, -20);
      delay(150);
      Robot.motorsStop();
      
      lastLeftMotor = 85;
      lastRightMotor = -20;
    }
    else if(mindex==3){
      //Robot.turn(-5);
      if (n%10==0){
        Robot.text("Left", 10, 50);
      }
      //Robot.motorsStop();
      //Robot.motorsWrite(85, -45);
      Robot.motorsWrite(-20, 85);
//      delay(150);
//      Robot.motorsStop();
      
      lastLeftMotor = -20;
      lastRightMotor = 85;
    }
    else if (mindex==0){
      //Robot.turn(-10);
      if (n%10==0){
        Robot.text("Rightmost", 10, 50);
      }
      //Robot.motorsStop();
      //Robot.motorsWrite(-75, 85);
      Robot.motorsWrite(85, -40);
      //delay(150);
      //Robot.motorsStop();
      lastLeftMotor = 85;
      lastRightMotor = -40;
    }
    else if (mindex==4){
      //Robot.motorsStop();
      if (n%10==0){
        Robot.text("Leftmost", 10, 50);
      }
      //Robot.motorsWrite(85, -75);
      Robot.motorsWrite(-40, 85);
//      delay(150);
//      Robot.motorsStop();
      
      lastLeftMotor = -40;
      lastRightMotor = 85;
      //Robot.turn(10);
    }
    else {
      Robot.motorsWrite(lastLeftMotor, lastRightMotor);
    }
   }
   
   else{
      Robot.motorsWrite(lastLeftMotor, lastRightMotor);
   }
  }


