// Close Encounters of the Third Kind - 5 note motif
// D5, E5, C5, C4, G4

const int speakerPin = 8;

int notes[]    = {587, 659, 523, 262, 392};
int durations[] = {500, 500, 500, 500, 1000};

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    tone(speakerPin, notes[i], durations[i]);
    delay(durations[i] + 50); // small gap between notes
  }
  delay(2000); // pause before repeating
}
