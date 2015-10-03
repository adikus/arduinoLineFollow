
#include <ArduinoRobot.h>
#include <NewPing.h>

int TRIGGER_PIN = 12;
int ECHO_PIN = 11;
int MAX_DISTANCE = 200;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  // initialize the robot
  Robot.begin();

  // initialize the screen
  Robot.beginTFT();
}
void loop() {
  delay(5); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping();
  Robot.stroke(0, 0, 0);              // choose the color black
  Robot.text("Hello World", 0, 0);  // print the text
}
