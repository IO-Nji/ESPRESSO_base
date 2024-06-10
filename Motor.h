
#include <Servo.h>
#include "ServoEasing.hpp"


ServoEasing ServoH;
Servo ServoL;
Servo ServoR;

static const int ServoHpin = D6;
static const int ServoLpin = D7;
static const int ServoRpin = D5;

void motorSetup();
void headTurn();
void moveMotors(Servo servo1, int targetPosition1, Servo servo2, int targetPosition2, int speed, int servoRunTime);
void goStop();
void goFwd();
void goBkwd();
void goLeft();
void goRight();


void motorSetup() {

  // /********************************************************
  //  * Attach servo to pin and set servo to start position.
  //  *******************************************************/
  // Serial.println(F("Attach servo at pin " STR(ServoH_PIN)));
  ServoH.attach(ServoHpin, 90);
  ServoL.attach(ServoLpin);
  ServoR.attach(ServoRpin);

  delay(500);  // Wait for servo to reach start position.
}

void headTurn() {
  Serial.println(F("Move to 135 degree with 40 degree per second blocking"));
  ServoH.easeTo(180, 90);  // Blocking call, runs on all platforms

  Serial.println(F("Move to 45 degree  with 40 degree per second blocking"));
  ServoH.easeTo(10, 60);  // Blocking call, runs on all platforms
}

void moveMotors(Servo servo1, int targetPosition1, Servo servo2, int targetPosition2, int speed, int servoRunTime) {

  int currentPosition1 = servo1.read();  // get current position of servo1
  int currentPosition2 = servo2.read();  // get current position of servo2

  while (currentPosition1 != targetPosition1 || currentPosition2 != targetPosition2) {
    if (currentPosition1 < targetPosition1) {
      servo1.write(++currentPosition1);
    } else if (currentPosition1 > targetPosition1) {
      servo1.write(--currentPosition1);
    }

    if (currentPosition2 < targetPosition2) {
      servo2.write(++currentPosition2);
    } else if (currentPosition2 > targetPosition2) {
      servo2.write(--currentPosition2);
    }

    delay(speed);
  }

  delay(servoRunTime);  // hold the servos at their final positions for servoRunTime milliseconds
  servo1.write(90);
  servo2.write(90);
}

void goStop() {
  moveMotors(ServoL, 90, ServoR, 90, 30, 200);  // Move servo1 to 90 degrees and servo2 to 180 degrees at speed 1 and hold for 2000 milliseconds
}

void goFwd() {
  goStop();
  ServoH.easeTo(90, 90);
  moveMotors(ServoL, 80, ServoR, 100, 30, 500);  // Move servo1 to 90 degrees and servo2 to 180 degrees at speed 1 and hold for 2000 milliseconds
}

void goBkwd() {
  ServoH.easeTo(90, 90);
  goStop();
  moveMotors(ServoL, 100, ServoR, 80, 30, 500);  // Move servo1 to 90 degrees and servo2 to 180 degrees at speed 1 and hold for 2000 milliseconds
}

void goLeft() {
  ServoH.easeTo(120, 90);
  goStop();
  moveMotors(ServoL, 75, ServoR, 75, 30, 1000);  // Move servo1 to 90 degrees and servo2 to 180 degrees at speed 1 and hold for 2000 milliseconds
  ServoH.easeTo(90, 90);
}

void goRight() {
  ServoH.easeTo(60, 90);
  goStop();
  moveMotors(ServoL, 105, ServoR, 105, 30, 1000);  // Move servo1 to 90 degrees and servo2 to 180 degrees at speed 1 and hold for 2000 milliseconds
  ServoH.easeTo(90, 90);
}