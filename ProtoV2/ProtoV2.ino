// Servo library
#include <Servo.h>

/* 
  
M1:
IN1 = 8, IN2 = 9
EN1 = 10
M2:
EN2 = 11
IN3 = 12, IN4 = 7
*/

//M1:
#define IN1 8
#define IN2 9
#define EN1 10

//M2:
#define IN3 12
#define IN4 7 
#define EN2 11

#define B1_PIN 3
#define B2_PIN 4

#define STEER 6

#define FORWARD 1
#define BACKWARD 2
#define RIGHT 3
#define LEFT 4

#define CH1 A1
#define CH2 A2
#define POTPIN A0

int speed = 255/4;

int ch1; 
int ch2;
int ch3;

int steerval;    // variable to read the value from the analog pin

Servo steer;  // create servo object to control a servo

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

void motor_off () {
  

    analogWrite(EN1, 0);
    analogWrite(EN2, 0);

}

void servo_time () {
    for( int a = 0; a < 15; ++a ) {  
  // waits for the servo to get there
  }
}

void setup(){
  Serial.begin(9600); // Pour a bowl of Serial
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);
  
  pinMode(CH1, INPUT); 
  pinMode(CH2, INPUT);
  
  steer.attach(STEER);  // attaches the servo on pin 9 to the servo object
   steer.write(90);
}

void loop(){

  boolean Bu1 = digitalRead(B1_PIN);
  boolean Bu2 = digitalRead(B2_PIN);

  ch1 = pulseIn(CH1, HIGH, 25000);
  
delay(12);  ch2 = pulseIn(CH2, HIGH, 25000); 
  
  steerval = analogRead(POTPIN);   // reads the value of the potentiometer (value between 0 and 1023)
  steerval = map(steerval, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)

  //Serial.print("Bu1:");Serial.print(Bu1); Serial.print("  Bu2:");Serial.println(Bu2);

  Serial.print("Chan 1:");Serial.print(ch1); Serial.print("  Chan 2:");Serial.println(ch2);
  
//  if (ch2 > 1400) {
//    run_motors(speed, FORWARD);
//  }
//  else if (Bu1 == HIGH) { // run fwd
//    run_motors(speed, FORWARD);
//  }
//  
//  if (ch2 < 1400 ) {
//    run_motors(speed, BACKWARD);
//  }
//  else if (Bu2 == HIGH) { // run back
//    run_motors(speed, BACKWARD);
//  }
//  else { //run idle
//    motor_off();
//  }
  
  if (((ch1 < 1677) or (ch1 > 1725) )and ch1 != 0) {
    if (ch1 > 1810){
    steer.write(0);
    }
    else if (ch1 <1470){
    steer.write(180);  
    }
    else{
        steer.write(90);
    }
  }
    
  }
  
//  else if (analogRead(POTPIN) < 450 or analogRead(POTPIN) > 575) {
//    steer.write(steerval);  // sets the servo position according to the scaled value
//    servo_time();
//  }

   

  
