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

int in_speed = 0;
//boolean B1 = digitalRead(B1_PIN);
//boolean B2 = digitalRead(B2_PIN);
//boolean B3 = digitalRead(B1_PIN);
//boolean B4 = digitalRead(B2_PIN);

char fwd[8] = "Forward";
char bwd[9] = "Backward";

void change_direc (bool direct, int motor_num_) {
  if ((direct == HIGH or direct == LOW) && motor_num_ == 1) {
    digitalWrite(IN1, direct);
    digitalWrite(IN2, !direct);
  }

  else if ((direct == HIGH or direct == LOW) && motor_num_ == 2) {
    digitalWrite(IN3, direct);
    digitalWrite(IN4, !direct);
  }
}

void run_motors (int speed, char direc[], int motor_num) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed);

  if (direc == "Forward") {
    Serial.println("  fwd active  ");
    change_direc(HIGH, motor_num); //forward
  }

  else if (direc == "Backward") {
    Serial.println("  bwd active  ");
    change_direc(LOW, motor_num); //backward

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
//  if (irrecv.decode(&results)){
//      Serial.println(results.value, HEX);
//      irrecv.resume();
//      delay(250);
//  }
   
  int speed = in_speed;
  if ((in_speed <= 255) && (in_speed >= 0) ){
    if (results.value == 0x20DF40BF){
      in_speed + 5 ;
    }
    else if (results.value == 0x20DFC03F){
      in_speed - 5 ;
    }
  }
  
  if (results.value == 0x20DF02FD) {
    run_motors(in_speed, fwd, 1);
  }
  else if (results.value == 0x20DF609F) {
    run_motors(in_speed, bwd, 1);
  }

  20DFE01F

  20DF827D

  
  irrecv.resume();
}
