// Motor A
const int AIN1 = 6;
const int AIN2 = 7;
const int PWMA = 9;

// Motor B
const int BIN1 = 4;
const int BIN2 = 3;
const int PWMB = 2;

const int STBY = 5;

void setup() {
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); // take out of standby
}

void driveMotor(int ain1, int ain2, int pwmPin, int speed) {
  if (speed > 0) {
    digitalWrite(ain1, HIGH);
    digitalWrite(ain2, LOW);
  } else if (speed < 0) {
    digitalWrite(ain1, LOW);
    digitalWrite(ain2, HIGH);
    speed = -speed;
  } else {
    digitalWrite(ain1, LOW);
    digitalWrite(ain2, LOW);
  }
  analogWrite(pwmPin, speed);
}

void loop() {
  Serial.println("forward");
  driveMotor(AIN1, AIN2, PWMA, 200);
  driveMotor(BIN1, BIN2, PWMB, 200);
  delay(2000);

  Serial.println("stop");
  driveMotor(AIN1, AIN2, PWMA, 0);
  driveMotor(BIN1, BIN2, PWMB, 0);
  delay(1000);

  Serial.println("reverse");
  driveMotor(AIN1, AIN2, PWMA, -200);
  driveMotor(BIN1, BIN2, PWMB, -200);
  delay(2000);

  Serial.println("stop");
  driveMotor(AIN1, AIN2, PWMA, 0);
  driveMotor(BIN1, BIN2, PWMB, 0);
  delay(1000);
}
