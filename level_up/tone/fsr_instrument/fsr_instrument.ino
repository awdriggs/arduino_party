const int speakerPin = 8;

// three FSR sensors
const int fsr1 = A0;
const int fsr2 = A1;
const int fsr3 = A2;

// predefined notes: C4, E4, G4 (a C major chord)
const int noteC = 262;
const int noteE = 330;
const int noteG = 392;

const int threshold = 50; // minimum FSR reading to trigger a note

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  if (analogRead(fsr1) > threshold) {
    tone(speakerPin, noteC);
    Serial.println("C");
  } else if (analogRead(fsr2) > threshold) {
    tone(speakerPin, noteE);
    Serial.println("E");
  } else if (analogRead(fsr3) > threshold) {
    tone(speakerPin, noteG);
    Serial.println("G");
  } else {
    noTone(speakerPin);
  }

  delay(10);
}
