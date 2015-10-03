#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>


void setup() {
  // initialize the robot
  Robot.begin();
  Robot.beginTFT();
  
  // setup colors
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
int renderF = 20;

int lastLeftMotor = 50;
int lastRightMotor = 50;

int right = 1;
int left = -1;

void turn(int dir) {
  if (n%renderF==0){
    Robot.text(dir == right ? "Right" : "Left", 10, 50);
  }
  //Robot.motorStop();
  int p1 = 180;
  int p2 = 60;
  setMotorPower(getPowerLevel(p1, p2, dir), getPowerLevel(p2, p1, dir));
  setLastMotors(getPowerLevel(p1, p2, dir), getPowerLevel(p2, p1, dir));
}

void turnHard(int dir) {
  if (n%renderF==0){
    Robot.text(dir == right ? "Right H" : "Left H", 10, 50);
  }
  //Robot.motorStop();
  int p1 = 160;
  int p2 = -75;
  setMotorPower(getPowerLevel(p1, p2, dir), getPowerLevel(p2, p1, dir));
  setLastMotors(getPowerLevel(p1, p2, dir), getPowerLevel(p2, p1, dir));
}

void setLastMotors(int p1, int p2){
  lastLeftMotor = p1;
  lastRightMotor = p2;
}

int getPowerLevel(int p1, int p2, int dir) {
    if(dir > 0){
      return p1;
    }
    else {
      return p2;
    }
}

void setMotorPower(int m1, int m2){
  if (n%renderF==0){
    Robot.text(m1, 10, 100);
    Robot.text(m2, 10, 110);
  }
  
  Robot.motorsWrite(m1, m2);
  delay(50);
  Robot.motorsStop();
}

void loop() {
  n++;
  
  Robot.updateIR();
  
  int mindex = mini(Robot.IRarray);
  int minvalue = (int)Robot.IRarray[mindex];
  
  if (n%renderF==0){
    Robot.rect(0, 0, 80, 120); 
    Robot.text(minvalue,20,10);
    Robot.text(mindex,20,20);
  }

  if (minvalue<=450){
    if (mindex==2){
      setMotorPower(120, 120);
      setLastMotors(120, 120);
    }
    else if (mindex==1){
      turn(right);
    }
    else if(mindex==3){
      turn(left);
    }
    else if (mindex==0){
      turnHard(right);
    }
    else if (mindex==4){
      turnHard(left);
    }
    else {
      setMotorPower(lastLeftMotor, lastRightMotor);
    }
  }
  else{
    setMotorPower(lastLeftMotor, lastRightMotor);
  }
}


