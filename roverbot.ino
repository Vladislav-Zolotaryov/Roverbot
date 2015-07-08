#include <SoftwareSerial.h>

SoftwareSerial xbee(0, 1);

int leftSideSpeedPin = 5;
int rightSideSpeedPin = 6;
int leftSidePin = 4;
int rightSidePin = 7;

int time = 0;
int lastCommandTime = 0;

int currentAcceleration = 200;

int accelerationChangeMultiplier = 10;

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  digitalWrite(leftSideSpeedPin, LOW);   
  digitalWrite(rightSideSpeedPin, LOW);
}

void loop() {
  if (xbee.available()) {
    lastCommandTime = time;
    char command = xbee.read();
    Serial.write(command);
    switch (command) {
      case 'f':
         moveForward(currentAcceleration);
        break; 
      case 'b':
         moveBackwards(currentAcceleration);
        break; 
      case 'l':
         rotateLeft(currentAcceleration);
        break; 
      case 'r':
         rotateRight(currentAcceleration);
        break; 
      case 'i':
         incrementAcceleration();
        break;
      case 'd':
         decrementAcceleration();
        break;    
      default:
         stopMoving();
        break;  
    }
  }
  int delta = time - lastCommandTime;
  if (delta > 10000) {
     lastCommandTime = 0;
     stopMoving();
  }
  time++;
}

void incrementAcceleration() {
   if ((currentAcceleration + accelerationChangeMultiplier) <= 255) {
     currentAcceleration = currentAcceleration + accelerationChangeMultiplier;
   }
}

void decrementAcceleration() {
   if ((currentAcceleration - accelerationChangeMultiplier) >= 0) {
     currentAcceleration = currentAcceleration - accelerationChangeMultiplier;
   }
}

void rotateRight(int speed) {
  digitalWrite(leftSidePin, LOW);
  digitalWrite(rightSidePin, HIGH);

  analogWrite(leftSideSpeedPin, speed);
  analogWrite(rightSideSpeedPin, speed);
}

void rotateLeft(int speed) {
  digitalWrite(leftSidePin, HIGH);
  digitalWrite(rightSidePin, LOW);

  analogWrite(leftSideSpeedPin, speed);
  analogWrite(rightSideSpeedPin, speed);
}

void stopMoving() {
  digitalWrite(leftSidePin, LOW);
  digitalWrite(rightSidePin, LOW);

  analogWrite(leftSideSpeedPin, 0);
  analogWrite(rightSideSpeedPin, 0);
}

void moveBackwards(int speed) {
  digitalWrite(leftSidePin, LOW);
  digitalWrite(rightSidePin, LOW);

  analogWrite(leftSideSpeedPin, speed);
  analogWrite(rightSideSpeedPin, speed);
}

void moveForward(int speed) {
  digitalWrite(leftSidePin, HIGH);
  digitalWrite(rightSidePin, HIGH);

  analogWrite(leftSideSpeedPin, speed);
  analogWrite(rightSideSpeedPin, speed);
}
