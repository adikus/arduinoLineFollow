
int pinA = 12;
int pinB = 11;
int pinC = 10;
int pinD = 9;

void setup() {
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);
}

void loop() {
    analogWrite(pinA, 0);
    analogWrite(pinB, 0);
    analogWrite(pinC, 0);
    analogWrite(pinD, 0);
    delay(1000);
    analogWrite(pinA, 255);
    delay(1000);
    analogWrite(pinB, 255);
    delay(1000);
    analogWrite(pinC, 255);
    delay(1000);
    analogWrite(pinD, 255);
    delay(1000);
}

