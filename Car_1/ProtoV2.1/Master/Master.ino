//
//#define analogPin A0
//int raw = 0;
//int Vin = 5;
//float Vout = 0;
//float R1 = 12000;
//float R2 = 0;
//float buffer = 0;
//
//void setup()
//{
//  Serial.begin(9600);
//  pinMode(2, OUTPUT);
//  pinMode(3, OUTPUT);
//  pinMode(4, OUTPUT);
//}
//
//void loop()
//{
//  raw = analogRead(analogPin);
//  if (raw)
//  {
//    buffer = raw * Vin;
//    Vout = (buffer) / 1024.0;
//    buffer = (Vin / Vout) - 1;
//    R2 = R1 * buffer;
////    Serial.print("Vout: ");
////    Serial.println(Vout);
////    Serial.print("R2: ");
////    Serial.println(R2);
//  }
//  if (R2 > 5600 and R2 < 6600) {
//    analogWrite(3, 0);
//    digitalWrite(2, HIGH);
//    digitalWrite(4, LOW);
//  }
//  else if (R2 < 5600 and R2 > 4200) {
//    analogWrite(3, 0);
//    digitalWrite(2, LOW);
//    digitalWrite(4, HIGH);
//  }
//
//  else {
//    analogWrite(3, 255);
//  }
//}


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

#define steerOUT 5

#define steerPin A0
#define CH1 A1
#define CH2 A2

#define FORWARD 1
#define BACKWARD 2

int speed = 50;

int ch1;
int ch2;

int steerval;
int raw = 0;
int Vin = 5;
float Vout = 0;
float R1 = (12*1000);
float R2 = 0;
float buffer = 0;

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
    change_direc(LOW); //forward //high
  }

  else if (direc == 2) {
    Serial.println("  bwd active  ");
    change_direc(HIGH); //backward //low

  }
}

void motor_off () {
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
}


void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);

  pinMode(steerOUT, OUTPUT);
}

void loop() {
  ch1 = pulseIn(CH1, HIGH, 25000);
  delay(12);  ch2 = pulseIn(CH2, HIGH, 25000);

  int steermap = map((analogRead(steerPin)), 0, 1023, 0, 180);
  steerval = analogRead(steerPin);

  raw = analogRead(steerPin);

  if (ch2 > 2010) {
    run_motors(speed, FORWARD);
  }
  else if (ch2 < 1400 and ch2 != 0) {
    run_motors(speed, BACKWARD);
  }

  else { //run idle
    motor_off();
  }

  if (raw) {
    buffer = raw * Vin;
    Vout = (buffer) / 1024.0;
    buffer = (Vin / Vout) - 1;
    R2 = R1 * buffer;
  }

  if (ch1 > 2000) {
    analogWrite(steerOUT, 255);
  }
  else if (ch1 < 1470 and ch1 != 0) {
    analogWrite(steerOUT, 0);
  }
  else if (R2 > 6600){
    analogWrite(steerOUT, 255);
  }
  else if (R2 < 4200){
    analogWrite(steerOUT, 0);
  }
  else {
    analogWrite(steerOUT, 120);
  }

  if (R2 >= 5600 and R2 < 6600) {
    analogWrite(3, 0);
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
  }
  else if (R2 < 5600 and R2 > 4200) {
    analogWrite(3, 0);
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
  }

  else {
    analogWrite(3, 255);
  }

}

