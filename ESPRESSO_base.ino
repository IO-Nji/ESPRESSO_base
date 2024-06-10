#include "Access.h"
#include "TimeService.h"
// #include "Weather.h"
#include "Face.h"
#include "Led.h"
#include "Sense.h"
#include "Motor.h"
#include "Sound.h"

void startExe();
void acTionTest();
void idle();


void setup(void) {

  Serial.begin(115200);
  serverSetup();
  // senseSetup();
  timeSetup();
  soundSetup();
  ledSetup();
  timeLED(getTimeHour(), getTimeMin());
  faceSetup();
  cute.play(S_MODE2);
  motorSetup();
}

void loop(void) {

  cute.play(S_MODE1);
  timeClient.update();
  acTionTest();
  startExe();
  idle();
}

void startExe() {
  cute.play(S_SUPER_HAPPY);
  report("Hi! I am Espresso...", "ESPRESS0");
  cute.play(S_MODE1);
  addNews("...");
  addNews("I am made for O.");
  cute.play(S_MODE2);
  addNews("I run a webserver you can access:");
  cute.play(S_CONNECTION);
  addNews(LabSSID + getIP());
  sayTopic("HTTP/:" + getIP(), 1);
  addNews("My purpose... to be free.");
  cute.play(S_HAPPY_SHORT);
  ledLoop("green", 1);
  chase("yellow");
  cute.play(S_CUDDLY) ;
  chase("blue");
}

void acTionTest() {

  chase("green");
  cute.play(S_CONNECTION);
  blinkEyes();
  report("The machines are coming... ", "_wARNINg_");
  chase("yellow");
  report("Are the robots going to save you?", "nO-LABs");
  cute.play(S_MODE1);


  // TODO: RIGHT_TURN Look Right Say Right LED indicate right movement turn
  ledLoop("blue", 1);
  showFace(right);
  sayTopic("<<<", 2);
  goRight();
  showFace(front);
  sayTopic("---", 2);
  cute.play(S_OHOOH);
  blinkEyes();


  // TODO:Turn Left
  showFace(left);
  sayTopic(">>>", 2);
  goLeft();
  showFace(front);
  sayTopic("O", 2);
  cute.play(S_OHOOH2);
  blinkEyes();
  cute.play(S_FART1);


  // TODO: Go Forwards
  showFace(glare);
  sayTopic("->><<-", 2);
  goFwd();
  blinkEyes();
  cute.play(S_JUMP);


  // TODO: Move Backwards
  showFace(up);
  sayTopic("<<->>", 2);
  goBkwd();
  blinkEyes();
  cute.play(S_CONFUSED);
}

void idle() {
  // Idle state
  sayTopic("BoReD", 2);
  showFace(distress);
  sayTopic("zZZ", 2);
  chase("green");
  showFace(sleepy);
  displayTime(getDayMonth(), getDayWeek(), getTimeHour(), getTimeMin());

  for (int i = 0; i < 15; i++) {
    // Yawn moves
    chase("green");
    sayTopic("O", 2);
    timeLED(getTimeHour(), getTimeMin());
    sayTopic("o", 2);
    sayTopic(".", 2);
    sayTopic("o", 2);
    sayTopic("O", 2);
    sayTopic("o", 2);
    sayTopic(".", 2);
    delay(1000);
  }

  for (int i = 5; i > 0; i--) {
    // Drool Moves
    chase("blue");
    sayTopic(".", 2);
    delay(100);
    sayTopic(".,", 2);
    delay(100);
    sayTopic(".,z", 2);
    delay(100);
    sayTopic(".,zZ", 2);
    cute.play(S_SLEEPING);
    sayTopic(".,zZ", 2);
    delay(100);
    sayTopic(".,z", 2);
    delay(100);
    sayTopic(".,", 2);
    delay(100);
    sayTopic(".", 2);
    displayTime(getDayMonth(), getDayWeek(), getTimeHour(), getTimeMin());
    chase("green");
    delay(15000);
  }
}
