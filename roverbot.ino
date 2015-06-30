int leftSideSpeedPin = 5;
int rightSideSpeedPin = 6;
int leftSidePin = 4;
int rightSidePin = 7;

void setup() {

}

void loop() {
  moveForward(255);
}

void rotateRight(int speed) {
  digitalWrite(leftSidePin, HIGH);
  digitalWrite(rightSidePin, LOW);

  analogWrite(leftSideSpeedPin, speed);
  analogWrite(rightSideSpeedPin, speed);
}

void rotateLeft(int speed) {
  digitalWrite(leftSidePin, LOW);
  digitalWrite(rightSidePin, HIGH);

  analogWrite(leftSideSpeedPin, speed);
  analogWrite(rightSideSpeedPin, speed);
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
