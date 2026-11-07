const int ledPin = 5; // must be a PWM pin (~)

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // fade up
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);
    Serial.println(brightness);
    delay(8);
  }

  // fade down
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    Serial.println(brightness);
    delay(8);
  }
}
