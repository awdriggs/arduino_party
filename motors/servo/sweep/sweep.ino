//Sweeps a servo between 0 and 180 degrees

#include <Servo.h> //import the servo library

Servo myServo; //defins a variable "myServo" of type Servo.

void setup() {
  Serial.begin(9600);
  myServo.attach(9); //setting the servo data pin to d9
}

void loop() {
  //loop from 0 to 180 by 1. The angle is the position of the servo.
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle); //send the servo to current angle value.
    Serial.print("angle: ");
    Serial.println(angle);
    delay(15); //dealy gives the servo a little bit of time to get there.
  }
  //loop from 180 to 0 by 1. reversing the direction.
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle); //send the servo to current angle value
    Serial.print("angle: ");
    Serial.println(angle);
    delay(15); //dealy gives the servo a little bit of time to get there.
  }
}
