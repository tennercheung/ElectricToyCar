
/*

  Master for Car 2

*/

//M1:
#define EN1 6
#define IN1 8
#define IN2 9


//M2:
#define EN2 11
#define IN3 10
#define IN4 7

#define CH2 A2

#define FORWARD 1
#define BACKWARD 2

#define LEFT 3
#define RIGHT 4
#define CENTRE 5
#define LEFTBWD 6
#define RIGHTBWD 7

int speed = 50;
int turnDirection;

int ch2;


void change_direc (bool direct) {
  if ((direct == HIGH || direct == LOW)) {

    digitalWrite(IN1, !direct);
    digitalWrite(IN2, direct);
    digitalWrite(IN3, direct);
    digitalWrite(IN4, !direct);
  }
}

void run_motors (int speed, int direc) {


  if (direc == 1) {
    analogWrite(EN1, speed);
    analogWrite(EN2, speed);
    Serial.println("  fwd active  ");
    change_direc(HIGH); //forward //high
  }

  else if (direc == 2) {
    analogWrite(EN1, speed);
    analogWrite(EN2, speed);
    Serial.println("  bwd active  ");
    change_direc(LOW); //backward //low

  }
  else if (direc == 3) {
    analogWrite(EN1, speed * 1.25);
    analogWrite(EN2, speed * 0.75);
    change_direc(HIGH);
  }
  else if (direc == 4) {
    analogWrite(EN1, speed * 0.75);
    analogWrite(EN2, speed * 1.25);
    change_direc(HIGH);
  }
  else if (direc == 6) {
    analogWrite(EN1, speed * 0.75);
    analogWrite(EN2, speed * 1.25);
    change_direc(LOW);
  }
  else if (direc == 7) {
    analogWrite(EN1, speed * 1.25);
    analogWrite(EN2, speed * 0.75);
    change_direc(LOW);
  }
}

void motor_off () {
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
}


void setup()
{
  Serial.begin(115200);


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);


  pinMode(CH2, INPUT);

}

void loop() {
  ch2 = pulseIn(CH2, HIGH, 25000);
  Serial.println(ch2);
  // centre = 1481/1487
  

  if (ch2 >= 1750) {

      run_motors(speed, BACKWARD);

  }
  else if (ch2 <= 1250 and ch2 != 0) {

      run_motors(speed, FORWARD);

  }

  else { //run idle
    motor_off();
  }
}
