#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

int key;

void setup() {
  // initialize the robot
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSpeaker();
  
  // setup colors
  Robot.stroke(0,0,0);
  Robot.fill(255,200,200);

  Robot.text("Press left, right or down!", 10, 10);
  key = Robot.keyboardRead();
  while(key != BUTTON_LEFT && key != BUTTON_RIGHT && key != BUTTON_DOWN){
    delay(50);
    key = Robot.keyboardRead();
  }
  switch(key){
    case BUTTON_LEFT: Robot.text("LEFT", 10, 20); break;
    case BUTTON_RIGHT: Robot.text("RIGHT", 10, 20); break;
    case BUTTON_DOWN: Robot.text("RANDOM!?", 10, 20); break; 
    }
  //Robot.text(key == BUTTON_LEFT ? "LEFT" : "RIGHT", 10, 20);
}

int countBlack(uint16_t* a){
  int count = 0;
  for (int i=1; i<5;i++){
    if (a[i] <= 450){
      count++;
    }
  }
  return count;
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
int renderF = 1000;

int lastLeftMotor = 50;
int lastRightMotor = 50;

int right = 1;
int left = -1;
unsigned long time;
unsigned long timeSum;

int multiplier = 25;

unsigned long lineLastSeen = millis();
int uTurn = 0;

void turn(int dir) {
  if (n%renderF==0){
    Robot.text(dir == right ? "Right" : "Left", 10, 50);
  }
  //Robot.motorStop();
  int p1 = 7.2*multiplier;
  int p2 = 2.4*multiplier;
  setMotorPower(getPowerLevel(p1, p2, dir), getPowerLevel(p2, p1, dir));
  setLastMotors(getPowerLevel(p1, p2, dir), getPowerLevel(p2, p1, dir));
}

void turnHard(int dir) {
  if (n%renderF==0){
    Robot.text(dir == right ? "Right H" : "Left H", 10, 50);
  }
  //Robot.motorStop();
  int p1 = 6.4*multiplier;
  int p2 = -3*multiplier;
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
  if(time != NULL){
    timeSum += millis() - time;
  }
  time = millis();
  
  Robot.updateIR();
  
  int mindex = mini(Robot.IRarray);
  int minvalue = (int)Robot.IRarray[mindex];
  int ircount = countBlack(Robot.IRarray);
  
  if (n%renderF==0){
    Robot.rect(0, 0, 80, 120); 
    Robot.text(minvalue,20,10);
    Robot.text(mindex,20,20);
    Robot.text((int)(timeSum/(n-1)),20,70);
    Robot.text(n,20,80);
  }

  if(ircount > 1){
    if(key != BUTTON_DOWN){  
      Robot.text("JUNCTION",20,110);
    
      Robot.motorsWrite(-70,-70);
      delay(50);
      Robot.motorsStop();

//    //Junction actions
//    switch(key){
//      
//      //Choose left
//      case BUTTON_LEFT: 
//          int leftmost = 0; 
//            for (int i=0; i<5;i++){
//              if (Robot.IRarray[i] <= 450){
//                leftmost = i;
//              }
//            }
//            
//            Robot.turn(-8*leftmost);
//            break;
//            
//      //Choose right
//       case BUTTON_RIGHT:
//          int rightmost = 4;
//          
//          for (int i=4; i>=0;i--){
//            if (Robot.IRarray[i] <= 450){
//              rightmost = i;
//            }
//          }
//          Robot.rect(0, 0, 128, 160); 
//          Robot.text(rightmost,30,50);
//          Robot.turn(8*(4-rightmost));
//          break;
//
//      case BUTTON_DOWN:
//        int randNumber = random(2);
//        if(randNumber){
//           int leftmost = 0;
//
//          for (int i=0; i<5;i++){
//            if (Robot.IRarray[i] <= 450){
//              leftmost = i;
//            }
//          }
//          
//          Robot.turn(-8*leftmost);
//          }
//         else{
//            int rightmost = 4;
//            
//            for (int i=4; i>=0;i--){
//              if (Robot.IRarray[i] <= 450){
//                rightmost = i;
//              }
//            }
//            Robot.rect(0, 0, 128, 160); 
//            Robot.text(rightmost,30,50);
//            Robot.turn(8*(4-rightmost));
//          }
//      break;
//       
//      }
     
      if(key == BUTTON_LEFT){
      int leftmost = 0;

      for (int i=0; i<5;i++){
        if (Robot.IRarray[i] <= 450){
          leftmost = i;
        }
      }
      
      Robot.turn(-8*leftmost);
      }else{
        int rightmost = 4;
    
        for (int i=4; i>=0;i--){
          if (Robot.IRarray[i] <= 450){
            rightmost = i;
          }
        }
        Robot.rect(0, 0, 128, 160); 
        Robot.text(rightmost,30,50);
        
        Robot.turn(8*(4-rightmost));
      }
    }  
    return;   
  }

  if (minvalue<=450){
    lineLastSeen = millis();
    uTurn = 0;
    if (mindex==2){
      setMotorPower(4.8*multiplier, 4.8*multiplier);
      setLastMotors(4.8*multiplier, 4.8*multiplier);
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
    if(uTurn == 1){ 
      Robot.rect(0, 0, 128, 160); 
      Robot.text("TURNING",10,100);      
      Robot.turn(180);
      Robot.text("GTFO",10,100);      
      uTurn = 2;
    }else if(uTurn == 2){ 
      setMotorPower(4.8*multiplier, 4.8*multiplier);
      setLastMotors(4.8*multiplier, 4.8*multiplier);
    }else if(millis() - lineLastSeen > 1000){
      Robot.rect(0, 0, 128, 160); 
      Robot.text("BACKING UP",10,100);

      Robot.motorsWrite(-lastLeftMotor*0.5, -lastRightMotor*0.5);
      delay(1000);
      Robot.motorsStop();

      uTurn = 1;
    }else{
      setMotorPower(lastLeftMotor, lastRightMotor);
    }
  }
}


