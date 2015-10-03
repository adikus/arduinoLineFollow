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

int lastLeftMotor = 50;
int lastRightMotor = 50;

int right = 1;
int left = -1;

void straight() {
      if (n%10==0){
        Robot.text("Middle", 10, 50);
      }
      Robot.motorsWrite(75, 75);
      
      lastLeftMotor = 75;
      lastRightMotor = 75;
}

void turn(int direction) {
  if (n%10==0){
    Robot.text(direction == right ? "Right" : "Left", 10, 50);
  }
  //Robot.motorStop();
  int p1 = 85;
  int p2 = -20;
  setMotorPower(getPowerLevel(p1, p2, direction), getPowerLevel(p2, p1, direction));
}

void turnHard(int direction) {
  if (n%10==0){
    Robot.text(direction == right ? "Right H" : "Left H", 10, 50);
  }
  //Robot.motorStop();
  int p1 = 85;
  int p2 = -40;
  setMotorPower(getPowerLevel(p1, p2, direction), getPowerLevel(p2, p1, direction));
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
  Robot.motorsWrite(m1, m2);
  //delay(150);
  //Robot.motorsStop();
  
  lastLeftMotor = m1;
  lastRightMotor = m2;

  if (n%10==0){
    Robot.text(m1, 10, 100);
    Robot.text(m2, 10, 110);
  }
}

void loop() {
  n++;
  
  Robot.updateIR();
  
  int mindex = mini(Robot.IRarray);
  int minvalue = (int)Robot.IRarray[mindex];
  
  if (n%10==0){
    Robot.rect(0, 0, 80, 120); 
    Robot.text(minvalue,20,10);
    Robot.text(mindex,20,20);
  }

  if (minvalue<=450){
    if (mindex==2){
      straight();
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


