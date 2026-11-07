const int motorPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  digitalWrite(motorPin, HIGH);
  Serial.println("motor ON");
  delay(2000);
  digitalWrite(motorPin, LOW);
  Serial.println("motor OFF");
  delay(2000);
}
