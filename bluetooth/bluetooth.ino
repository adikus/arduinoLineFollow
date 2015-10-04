
int pinA = 12;
int pinB = 3;
int pinC = 4;
int pinD = 9;
int ledPin = 13;  // use the built in LED on pin 13 of the Uno
int leftLedPin = 6;
int rightLedPin = 10;
int state = 0;
boolean disco = false;

void setup() {
    // sets the pins as outputs:
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(leftLedPin, OUTPUT);
    pinMode(rightLedPin, OUTPUT);
    leftLed();

    Serial.begin(9600); // Default connection rate for my BT module
}

void loop() {
  
    analogWrite(ledPin, 0); //turn the LED off
    
    //if some data is sent, read it and save it in the state variable
    if(Serial.available() > 0){
      state = Serial.read();
      Serial.println(String(state));
      analogWrite(ledPin, 255);
    }
    
    switch (state) {
      case '0':
        analogWrite(pinA, 0);
        break;
      case '1':
        analogWrite(pinA, 255);
        break;
      case '2':
        analogWrite(pinB, 0);
        leftLed();
        break;
      case '3':
        analogWrite(pinB, 255);
        rightLed();
        break;
      case '4':
        analogWrite(pinC, 0);
        break;
      case '5':
        analogWrite(pinC, 255);
        break;
      case '6':
        analogWrite(pinD, 0);
        disco = false;
        analogWrite(pinB, 0); //back to default
        leftLed();
        break;
      case '7':
        analogWrite(pinD, 255);
        disco = true;
        break;
    }
    
    if (disco) {
      discoMode();
    }
    
}

void leftLed() {
  analogWrite(leftLedPin, 255);
  analogWrite(rightLedPin, 0);
}

void rightLed() {
  analogWrite(leftLedPin, 0);
  analogWrite(rightLedPin, 255);
}

void discoMode() {
  leftLed();
  delay(250);
  rightLed();
  delay(250);
}

