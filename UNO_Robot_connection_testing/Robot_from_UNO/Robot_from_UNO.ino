
#include <ArduinoRobot.h>

int pinA = TKD3;
int pinB = TKD4;
int pinC = TKD5;
int pinD = TKD1;

void setup() {
Robot.begin();
Robot.beginTFT();
}

void loop() {

int valA = digitalRead(pinA);
int valB = digitalRead(pinB);
int valC = digitalRead(pinC);
int valD = digitalRead(pinD);

char buf[50];
sprintf(buf, "values: %d, %d, %d, %d", valA, valB, valC, valD); 

Robot.stroke(0, 0, 0);
Robot.text(buf, 0, 0);
delay(50);
Robot.stroke(255, 255, 255);
Robot.text(buf, 0, 0);

}
