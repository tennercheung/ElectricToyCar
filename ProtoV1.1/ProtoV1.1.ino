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

//#include <IRremote.h>

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

#define POTPIN 0

//boolean override = false;

//const int RECV_PIN = 2;
//IRrecv irrecv(RECV_PIN);
//decode_results results;

//int in_speed = 0;




void change_direc (bool direct) {
  if ((direct == HIGH || direct == LOW)) {


    digitalWrite(IN1, !direct);
    digitalWrite(IN2, direct);
    digitalWrite(IN3, !direct);
    digitalWrite(IN4, direct);
  }
}



void run_motors (int speed, int direc) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed);

  if (direc == 1) {
    Serial.println("  fwd active  ");
   Serial.print(speed);
    change_direc(HIGH); //forward
  }

  else if (direc == 2) {
    Serial.println("  bwd active  ");
        Serial.print(speed);
    change_direc(LOW); //backward

  }

}

void motor_off (int speed, int direc_) {
  if (direc_ == 3) {
    Serial.println("  left active  ");
    analogWrite(EN1, speed/2);
    analogWrite(EN2, 0);
  }

  else if (direc_ == 4) {
    Serial.println("  right active  ");
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
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);
  
}

void loop(){

  boolean Bu1 = digitalRead(B1_PIN);
  boolean Bu2 = digitalRead(B2_PIN);
  boolean Bu3 = digitalRead(B3_PIN);
  boolean Bu4 = digitalRead(B4_PIN);

  int speed = analogRead(POTPIN)/4;

  Serial.print("Bu1:");Serial.println(Bu1);
  Serial.print("Bu2:");Serial.println(Bu2);
  Serial.print("Bu3:");Serial.println(Bu3);
  Serial.print("Bu4:");Serial.println(Bu4);

  Serial.print("speed:");Serial.println(speed);
  
  if ( Bu1 == HIGH) { // run fwd
      run_motors(speed, 1);
  }
  
  else if (Bu2 == HIGH) { // run back
    run_motors(speed, 2);
  }

  if ( Bu3 == HIGH) { // run right
    motor_off(speed, 3);
  }

  else if ( Bu4 == HIGH) { // run left
    motor_off(speed, 4);
  }

  else { //run idle
    motor_off(0, 0);
  }

}


