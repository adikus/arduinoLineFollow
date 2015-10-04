
#include <NewPing.h>
#include <ArduinoRobot.h>

int TRIGGER_PIN = A3; // Arduino pin tied to trigger pin on the ultrasonic sensor.
int ECHO_PIN = A4; // Arduino pin tied to echo pin on the ultrasonic sensor.
int MAX_DISTANCE = 400; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

boolean go = false;

void setup() {
//pinMode (TRIGGER_PIN, INPUT);
//pinMode (ECHO_PIN, INPUT);
Robot.begin();
Robot.beginTFT();
}

void loop() {

//String dat = String(uS / US_ROUNDTRIP_CM);
//char buf[25];
//dat.toCharArray(buf,25);

unsigned long long uS = 0;

int reading_no = 0;
for (int i; i<10; i++) {
  unsigned long reading = sonar.ping();
  if (reading > 0) {
    uS += reading; // Send ping, get ping time in microseconds (uS).
    reading_no++;
  }
  delay(50);
}

//erase previous msg
Robot.stroke(255, 255, 255);
if (go) {
  Robot.text("Good to go.", 0, 0);
} else {
  Robot.text("Too close!", 0, 0);
}

if (reading_no == 0) {
  go = false;
} else {
  float distance = uS / reading_no / US_ROUNDTRIP_CM;
  go = distance > 100;
}

//print new msg
Robot.stroke(0, 0, 0);
if (go) {
  Robot.text("Good to go.", 0, 0);
} else {
  Robot.text("Too close!", 0, 0);
}

/*
char buf[50];
dtostrf(distance, 8, 1, buf); 

Robot.stroke(0, 0, 0);
Robot.text(buf, 0, 0);
delay(500);
Robot.stroke(255, 255, 255);
Robot.text(buf, 0, 0);
*/

}
