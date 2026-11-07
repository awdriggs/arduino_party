const int ledPin = 5; // must be a PWM pin (~)
const int potPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue  = analogRead(potPin);
  int brightness = map(potValue, 0, 1023, 0, 255);

  analogWrite(ledPin, brightness);

  Serial.print("pot: ");
  Serial.print(potValue);
  Serial.print("  brightness: ");
  Serial.println(brightness);

  delay(50);
}
