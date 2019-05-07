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

#define IN1 8
#define IN2 9
#define EN1 10

#define IN3 12
#define IN4 13
#define EN2 11

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;



void change_direc (bool direct, int motor_num) {
  if ((direct == HIGH or direct == LOW) && motor_num == 1) {
    digitalWrite(IN1, direct);
    digitalWrite(IN2, !direct);
  }

  else if ((direct == HIGH or direct == LOW) && motor_num == 2) {
    digitalWrite(IN3, direct);
    digitalWrite(IN4, !direct);
  }
}

void run_motors (int speed, char direc[], int movement) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed);

  if (movement == 25) {
    Serial.println("  fwd active  ");
    change_direc(HIGH, 1); //forward
  }

  else if (movement == 50) {
    Serial.println("  bwd active  ");
    change_direc(LOW, 1); //backward

  }

}

void motor_off (char direc[]) {
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
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
