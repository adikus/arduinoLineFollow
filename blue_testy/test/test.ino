#include <ArduinoRobot.h>

void setup(){
  // initialize the robot
  Robot.begin();

  // open the serial port to send the information of what you are reading
  Serial.begin(9600);
}

void loop(){
  digitalWriteTKDs();
}

// write all TKD outputs on the Control Board as digital outputs
void digitalWriteTKDs() {
  int tk0 = 100;
  for(int i=0;i<8;i++) {
    // turn all the pins on
    Robot.analogWrite(i, HIGH);
    Serial.print("on\n");
    delay(500);
  
    // turn all the pins off
    Robot.analogWrite(i, LOW);
    Serial.print("off\n");
    delay(500);
  }
}
