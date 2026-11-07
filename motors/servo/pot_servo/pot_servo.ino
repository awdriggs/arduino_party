#include <Servo.h> //import the servo library

Servo myServo; //assign variable to a servo object

const int potPin = A0; //assign a pin to red the pot

void setup() {
  Serial.begin(9600);
  myServo.attach(9); //set servo data to pin 9
}

void loop() {
  int potValue = analogRead(potPin); //read in the pots value, this is between 0 and 1023
  int angle = map(potValue, 0, 1023, 0, 180); //convert from an analog reading to degrees
  myServo.write(angle); //tell the servo where to go!
  Serial.print("angle: ");
  Serial.println(angle);
  delay(15);
}
