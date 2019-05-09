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

#define B1_PIN 3
#define B2_PIN 4
#define B3_PIN 5
#define B4_PIN 6

#define POT_PIN 0

boolean override = false;

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

int in_speed = 0;



char fwd[8] = "Forward";
char bwd[9] = "Backward";
char left[5] = "Left";
char right[6] = "Right";

int hold = 0xFFFFFFFF;
volatile int temp_read = 0;

void change_direc (bool direct, int direc__) {
  if ((direct == HIGH || direct == LOW) && direc__ == 1) {
Serial.println("  leeeeeeee active  ");
     
    digitalWrite(IN1, direct);
    digitalWrite(IN2, !direct);
  }

  else if ((direct == HIGH || direct == LOW) && direc__ == 2) {
    
Serial.println("  reeeeeee active  ");
    digitalWrite(IN3, direct);
    digitalWrite(IN4, !direct);
  }
}



void run_motors (int speed, int direc) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed);

  if (direc == 1) {
    Serial.println("  fwd active  ");
   Serial.print(speed);
    change_direc(HIGH, direc); //forward
  }

  else if (direc == 2) {
    Serial.println("  bwd active  ");
        Serial.print(speed);
    change_direc(LOW, direc); //backward

  }

}

void motor_off (int speed, int direc_) {
  if (direc_ == 3) {
    analogWrite(EN1, speed/2);
    analogWrite(EN2, 0);
  }

  else if (direc_ == 4) {
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

  pinMode(B1_PIN, INPUT);
  pinMode(B2_PIN, INPUT);
  pinMode(B3_PIN, INPUT);
  pinMode(B4_PIN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);
  
}

void loop(){
//  if (irrecv.decode(&results)){
//      Serial.println(results.value, HEX);
//      irrecv.resume();
//      delay(250);
//  }
  boolean Bu1 = digitalRead(B1_PIN);
  boolean Bu2 = digitalRead(B2_PIN);
  boolean Bu3 = digitalRead(B3_PIN);
  boolean Bu4 = digitalRead(B4_PIN);

//  int speed = analogRead(POT_PIN);
int speed = 255;
//  if (override = true) {
//    speed = in_speed;
//  } 
  if ((in_speed <= 255) && (in_speed >= 0) ){
    if (results.value == 0x20DF40BF){
      in_speed + 5 ;
    }
    else if (results.value == 0x20DFC03F){
      in_speed - 5 ;
    }
  }
  Serial.print("Bu1:");Serial.println(Bu1);
  Serial.print("Bu2:");Serial.println(Bu2);
  Serial.print("Bu3:");Serial.println(Bu3);
  Serial.print("Bu4:");Serial.println(Bu4);

  Serial.print("speed:");Serial.println(speed);
  
  if (results.value == 0x20DF02FD || Bu1 == HIGH) {
      run_motors(speed, 1);
  }
  else if (results.value == 0x20DF609F || Bu2 == HIGH) {
    run_motors(speed, 2);
  }

  if (results.value == 0x20DFE01F || Bu3 == HIGH) {
    motor_off(speed, 3);
  }

  else if (results.value == 0x20DF827D || Bu4 == HIGH) {
    motor_off(speed, 4);
  }
    
//  irrecv.resume();
}
