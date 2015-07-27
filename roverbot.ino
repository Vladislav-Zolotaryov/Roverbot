#include <SoftwareSerial.h>
#include <Servo.h>
#include <NewPing.h>

int headServoPosition = 90;

int leftSideSpeedPin = 5;
int rightSideSpeedPin = 6;
int leftSidePin = 4;
int rightSidePin = 7;
int headServoPin = 10;
int sensorTriggerPin = 8;
int sensorEchoPin = 9;

int sensorMaxDistance = 200;

int time = 0;
int lastCommandTime = 0;

int currentAcceleration = 210;

int accelerationChangeMultiplier = 10;

boolean autoExplorerMode = false;

Servo headServo;
SoftwareSerial xbee(0, 1);
NewPing sonar(sensorTriggerPin, sensorEchoPin, sensorMaxDistance);

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  
  digitalWrite(leftSideSpeedPin, LOW);   
  digitalWrite(rightSideSpeedPin, LOW);
  
  headServo.attach(10);
  headServo.write(headServoPosition);
  delay(1000);
}

void loop() {
  autoExplore();
}
/*
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
  int lastCommandDelta = time - lastCommandTime;
  if (lastCommandDelta > 10000) {
     lastCommandTime = 0;
     stopMoving();
  }
  time++;
}*/

void autoExplore() {
   int distanceCm = convertDistance(sonar.ping() / US_ROUNDTRIP_CM);
   if (distanceCm < 30) {
     stopMoving();
     int leftDistanceCm = convertDistance(lookLeft());
     int rightDistanceCm = convertDistance(lookRight());
     if (rightDistanceCm > leftDistanceCm) {
       rotateExactlyToRight();
     } else {
       rotateExactlyToLeft();
     }
     lookForward();
   } else {
     moveForward(currentAcceleration);
   }
}

int convertDistance(int distance) {
  if (distance == 0) {
    distance = sensorMaxDistance + 10;
  }
  return distance;
}

int look(int servoPosition) {
  headServo.write(servoPosition);
  delay(1000);
  return sonar.ping() / US_ROUNDTRIP_CM;  
}

int lookForward() {
  headServoPosition = 90;
  return look(headServoPosition);
}

int lookLeft() {
  headServoPosition = 0;
  return look(headServoPosition);
}

int lookRight() {
  headServoPosition = 180;
  return look(headServoPosition);
}

void rotateExactlyToLeft() {
  rotateLeft(currentAcceleration);  
  delay(2000);
  stopMoving();
}

void rotateExactlyToRight() {
  rotateRight(currentAcceleration);  
  delay(2000);
  stopMoving();
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
