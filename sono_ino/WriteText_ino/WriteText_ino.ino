
#include <ArduinoRobot.h>

int TRIGGER_PIN = 12;

void setup() {
  // initialize the robot
  Robot.begin();

  // initialize the screen
  Robot.beginTFT();
  pinMode(TRIGGER_PIN, INPUT); 
}
void loop() {
  delay(5); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int d = digitalRead(TRIGGER_PIN);
  String dat = String(d);
  char buf[25];
  dat.toCharArray(buf,25);
  Robot.text(buf, 0, 0);  // print the text
}
