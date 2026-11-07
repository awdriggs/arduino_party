#include <Stepper.h>

const int stepsPerRevolution = 516; // 516 steps = one full revolution with gearing
Stepper myStepper(stepsPerRevolution, 6, 7, 4, 3); // coil A: pins 6,7 | coil B: pins 4,3

const int PWMA = 9;
const int PWMB = 2;
const int STBY = 5;

const int potPin     = A0;
const int btnForward = 10;
const int btnBack    = 11;

void setup() {
  Serial.begin(9600);

  // enable the motor driver
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(PWMA, HIGH);
  digitalWrite(PWMB, HIGH);
  digitalWrite(STBY, HIGH);

  // buttons use internal pullup, no resistor needed
  pinMode(btnForward, INPUT_PULLUP);
  pinMode(btnBack,    INPUT_PULLUP);
}

void loop() {
  int potValue = analogRead(potPin);
  int speed = map(potValue, 0, 1023, 1, 24); // map pot to RPM range
  myStepper.setSpeed(speed);

  if (digitalRead(btnForward) == LOW) {
    myStepper.step(8);
    Serial.print("forward  speed: ");
    Serial.println(speed);
  } else if (digitalRead(btnBack) == LOW) {
    myStepper.step(-8);
    Serial.print("back  speed: ");
    Serial.println(speed);
  }
}
