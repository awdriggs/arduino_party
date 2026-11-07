const int speakerPin = 8;
const int fsrPin     = A0;

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  int fsrReading = analogRead(fsrPin);
  Serial.println(fsrReading);

  if (fsrReading > 50) { // only play when the sensor is pressed
    int frequency = map(fsrReading, 50, 1023, 100, 2000);
    tone(speakerPin, frequency);
  } else {
    noTone(speakerPin);
  }

  delay(10);
}
