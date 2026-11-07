#include <Stepper.h>

const int stepsPerRevolution = 516; // 516 steps = one full revolution with gearing
Stepper myStepper(stepsPerRevolution, 6, 7, 4, 3); // coil A: pins 6,7 | coil B: pins 4,3

const int PWMA = 9;
const int PWMB = 2;
const int STBY = 5;

const int btnForward = 11;
const int btnBack    = 12;

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

  myStepper.setSpeed(24); // RPM — increase to go faster, decrease to go slower
}

void loop() {
  if (digitalRead(btnForward) == LOW) {
    myStepper.step(8); // steps per loop iteration — increase for faster movement
    Serial.println("forward");
  } else if (digitalRead(btnBack) == LOW) {
    myStepper.step(-8); // negative = reverse direction
    Serial.println("back");
  }
}
