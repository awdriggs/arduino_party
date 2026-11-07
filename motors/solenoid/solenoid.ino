const int solenoidPin = 2;
const int btnPin      = 3;

void setup() {
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP); // button uses internal pullup, no resistor needed
}

void loop() {
  if (digitalRead(btnPin) == LOW) {
    digitalWrite(solenoidPin, HIGH); // open solenoid
    Serial.println("ON");
  } else {
    digitalWrite(solenoidPin, LOW);  // close solenoid
    Serial.println("OFF");
  }
}
