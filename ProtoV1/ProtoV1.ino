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

//M1:
#define IN1 8
#define IN2 9
#define EN1 10

//M2:
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
char left[5] = "Left";
char right[6] = "Right";

int hold = 0xFFFFFFFF;
volatile int temp_read = 0;

void change_direc (bool direct, char direc_[]) {
  if ((direct == HIGH or direct == LOW) && direc_ == "Forward") {
    digitalWrite(IN1, direct);
    digitalWrite(IN2, !direct);
  }

  else if ((direct == HIGH or direct == LOW) && direc_ == "Backward") {
    digitalWrite(IN3, direct);
    digitalWrite(IN4, !direct);
  }
}



void run_motors (int speed_, char direc[]) {
  analogWrite(EN1, speed_);
  analogWrite(EN2, speed_);

  if (direc == "Forward") {
    Serial.println("  fwd active  ");
    change_direc(HIGH, direc); //forward
  }

  else if (direc == "Backward") {
    Serial.println("  bwd active  ");
    change_direc(LOW, direc); //backward

  }

}

void motor_off (int speed, char direc[]) {
  if (direc == "Left") {
    analogWrite(EN1, speed/2);
    analogWrite(EN2, 0);
  }

  else if (direc == "Right") {
    analogWrite(EN1, 0);
    analogWrite(EN2, speed/2);
  }
  
  else {
    analogWrite(EN1, 0);
    analogWrite(EN2, 0);
  }
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


   
  int* speed = in_speed;
  if ((in_speed <= 255) && (in_speed >= 0) ){
    if (results.value == 0x20DF40BF){
      in_speed + 5 ;
    }
    else if (results.value == 0x20DFC03F){
      in_speed - 5 ;
    }
  }
  
  if (results.value == 0x20DF02FD) {
    temp_read = results.value;
    if ( (temp_read == hold) || (temp_read = 0)){
      run_motors(&speed, fwd);
    }
    temp_read = 0;
  }
  else if (results.value == 0x20DF609F) {
    run_motors(&speed, bwd);
  }

  if (results.value == 0x20DFE01F) {
    motor_off(&speed, left);
  }

  else if (results.value == 0x20DF827D) {
    motor_off(&speed, right);
  }
    
  irrecv.resume();
}
