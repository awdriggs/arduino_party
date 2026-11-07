const int motorPin = 2;
const int potPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  int speed = map(potValue, 0, 1023, 0, 255);
  analogWrite(motorPin, speed);
  Serial.println(speed);
  delay(100);
}
