// Servo library
#include <Servo.h>
#define STEER 6

#define steerIN A3
#define posHome 90
#define posLeft 60
#define posRight 120

Servo steer;
boolean steerCheck[3] = {true, false, true};
int analogNum;

void setup() {
  Serial.begin(115200); // Pour a bowl of Serial

  steer.attach(STEER);  // attaches the servo on pin 9 to the servo object
  steer.write(posHome);
}

void loop() {
  analogNum = analogRead(steerIN);
  Serial.println(analogNum);
  if (analogNum > 500) {
    steerCheck[2] = steerCheck[1];
    steerCheck[1] = steerCheck[0];
    steerCheck[0] = true;

  }
  else if (analogNum < 500) {
    steerCheck[2] = steerCheck[1];
    steerCheck[1] = steerCheck[0];
    steerCheck[0] = false;
  }
  if (steerCheck[0] == true and steerCheck[1] == true and steerCheck[2] == true) {
    steer.write(posRight);
  }
  else if (steerCheck[0] == false and steerCheck[1] == false and steerCheck[2] == false) {
    steer.write(posLeft);
  }
  else {
    steer.write(posHome);
  }
}
