
// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------
#include <NewPing.h>

int ledPin = 13;
int TRIGGER_PIN = 12; // Arduino pin tied to trigger pin on the ultrasonic sensor.
int ECHO_PIN = 11; // Arduino pin tied to echo pin on the ultrasonic sensor.
int MAX_DISTANCE = 200; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
pinMode (ledPin, OUTPUT);
Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
delay(5); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
Serial.print("Ping: ");
Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
Serial.println("cm");

if (uS / US_ROUNDTRIP_CM > 20) { // This is where the LED On/Off happens
digitalWrite(ledPin,HIGH); // When the Red condition is met, the Green LED should turn off

}
else {
digitalWrite(ledPin,LOW);

}
if (uS / US_ROUNDTRIP_CM <= 20 || uS / US_ROUNDTRIP_CM >= 0){

}
else {
Serial.print(uS / US_ROUNDTRIP_CM);
Serial.println(" cm");
}
delay(5);
}
