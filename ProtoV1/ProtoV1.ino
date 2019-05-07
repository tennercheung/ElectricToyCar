/* 
  wasd = 20DF02FD, 20DFE01F, 20DF609F, 20DF827D
  + , - (pwm) = 20DF40BF, 20DFC03F

M1:
IN1 = 8, IN2 = 9
EN1 = 10

M2:
EN2 = 11
IN3 = 12, IN4 = 13
*/

#include <IRremote.h>

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void change_direc (bool direct) {
  if (direct == HIGH or direct == LOW) {
    digitalWrite(in1Pin, direct);
    digitalWrite(in2Pin, !direct);
  }
}

void run_motors (int speed, char direc[], int movement) {
  analogWrite(enablePin, speed);

  if (movement == 25) {
    Serial.println("  fwd active  ");
    change_direc(HIGH); //forward
  }

  else if (movement == 50) {
    Serial.println("  bwd active  ");
    change_direc(LOW); //backward

  }

}

void motor_off (char direc[]) {
  analogWrite(enablePin, 0);
}

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
        delay(250);
  }

  
}
