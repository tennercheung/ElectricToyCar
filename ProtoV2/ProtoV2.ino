

/*

  M1:
  IN1 = 8, IN2 = 9
  EN1 = 6
  M2:
  EN2 = 11
  IN3 = 10, IN4 = 7
*/

//M1:
#define IN1 8
#define IN2 9
#define EN1 6

//M2:
#define IN3 10
#define IN4 7
#define EN2 11

#define BU1 3
#define BU2 4

#define FORWARD 1
#define BACKWARD 2

#define CH1 A1
#define CH2 A2
#define POTPIN A0

#define steerOUT 5


int speed = 50;

int ch1;
int ch2;

boolean Bu1 = digitalRead(BU1);
boolean Bu2 = digitalRead(BU2);

int steerval;    // variable to read the value from the analog pin

void change_direc (bool direct) {
  if ((direct == HIGH || direct == LOW)) {

    digitalWrite(IN1, !direct);
    digitalWrite(IN2, direct);
    digitalWrite(IN3, direct);
    digitalWrite(IN4, !direct);
  }
}


void run_motors (int speed, int direc) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed);

  if (direc == 1) {
    Serial.println("  fwd active  ");
    change_direc(HIGH); //forward
  }

  else if (direc == 2) {
    Serial.println("  bwd active  ");
    change_direc(LOW); //backward

  }
}

void motor_off () {
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
}

void setup() {
  Serial.begin(115200); // Pour a bowl of Serial

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);

  pinMode(BU1, INPUT_PULLUP);
  pinMode(BU2, INPUT_PULLUP);

  pinMode(steerOUT, OUTPUT);

}

void loop() {

  ch1 = pulseIn(CH1, HIGH, 25000);
  delay(12);  ch2 = pulseIn(CH2, HIGH, 25000);

  int steermap = map((analogRead(POTPIN)), 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
  steerval = analogRead(POTPIN);
  //  Serial.print("Bu1:");Serial.print(Bu1);
  //  Serial.print("  Bu2:");Serial.println(Bu2);

  //    Serial.print("Chan 1:"); Serial.println(ch1);
  //  Serial.print("  Chan 2:"); Serial.println(ch2);
  //  Serial.print("angle"); Serial.println(steerval);

  if (ch2 > 2010) {
    run_motors(speed, FORWARD);
  }
  else if (ch2 < 1400 and ch2 != 0) {
    run_motors(speed, BACKWARD);
  }
  else if ( (Bu1 == LOW) and (Bu2 == HIGH) ) { // run fwd
    run_motors(speed, FORWARD);
  }


  else if ( (Bu2 == LOW) and (Bu1 == HIGH) ) { // run back
    run_motors(speed, BACKWARD);
  }

  else { //run idle
    motor_off();
  }

  int d = 3;


  if (ch1 > 2000) {
    analogWrite(steerOUT, 255);
    d = 1;
    //Serial.println("1");
  }
  else if (ch1 < 1470 /*and ch1 != 0*/) {
    analogWrite(steerOUT, 0);
    d = 2;
    //Serial.println("2");
  }
  //else {
  //analogWrite(steerOUT, 120);
  //Serial.println("3");
  //}
  else {
    analogWrite(steerOUT, 120);
  }
  Serial.println(d);


  //  else if ((steermap < 70 or steermap > 120) and ((ch1 > 1677) or (ch1 < 1725))) {
  //    if (steerval > 700) {
  //      analogWrite(steerOUT, 255);
  //      Serial.println("1_____");
  //    }
  //    else if (steerval < 300) {
  //      analogWrite(steerOUT, 0);
  //      Serial.println("2_____");
  //    }
  //    else {
  //      analogWrite(steerOUT, 120);
  //      Serial.println("3_____");
  //
  //    }
  //  }
}
