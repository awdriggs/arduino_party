// Motor A
const int AIN1 = 6;
const int AIN2 = 7;
const int PWMA = 9;

// Motor B
const int BIN1 = 4;
const int BIN2 = 3;
const int PWMB = 2;

const int STBY  = 5;
const int potPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);

  // set direction forward
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void loop() {
  int potValue = analogRead(potPin);
  int speed = map(potValue, 0, 1023, 0, 255);

  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);

  Serial.print("speed: ");
  Serial.println(speed);

  delay(50);
}
