// Motor A
const int AIN1 = 6;
const int AIN2 = 7;
const int PWMA = 9;

// Motor B
const int BIN1 = 4;
const int BIN2 = 3;
const int PWMB = 2;

const int STBY   = 5;
const int potPin  = A0;
const int btnPin  = 12;

bool forward = true;
bool lastBtnState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);

  digitalWrite(STBY, HIGH);
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
  bool btnState = digitalRead(btnPin);
  if (btnState == LOW && lastBtnState == HIGH) {
    forward = !forward;
    Serial.println(forward ? "direction: forward" : "direction: reverse");
    delay(50);
  }
  lastBtnState = btnState;

  int potValue = analogRead(potPin);
  int speed = map(potValue, 0, 1023, 0, 255);
  int actualSpeed = forward ? speed : -speed;

  driveMotor(AIN1, AIN2, PWMA, actualSpeed);
  driveMotor(BIN1, BIN2, PWMB, actualSpeed);

  Serial.print("speed: ");
  Serial.print(speed);
  Serial.print("  direction: ");
  Serial.println(forward ? "forward" : "reverse");

  delay(50);
}
