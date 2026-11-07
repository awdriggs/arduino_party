#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

const int ledPin = 5; // PWM pin

// sensing range in mm — adjust based on your setup
const int minDist = 15;
const int maxDist = 500;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  if (!sensor.begin()) {
    Serial.println("sensor not found, check wiring");
    while (1);
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t measurement;
  sensor.rangingTest(&measurement, false);

  if (measurement.RangeStatus != 4) {
    int distance   = measurement.RangeMilliMeter;
    // closer = brighter: invert the map by swapping 255 and 0
    int brightness = map(distance, minDist, maxDist, 255, 0);
    brightness     = constrain(brightness, 0, 255);

    analogWrite(ledPin, brightness);

    Serial.print("distance (mm): ");
    Serial.print(distance);
    Serial.print("  brightness: ");
    Serial.println(brightness);
  } else {
    analogWrite(ledPin, 0); // out of range, turn off LED
    Serial.println("out of range");
  }

  /* delay(50); */
}
