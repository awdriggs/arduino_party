#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for serial monitor to open

  if (!sensor.begin()) {
    Serial.println("sensor not found, check wiring");
    while (1); // stop here if sensor isn't found
  }

  Serial.println("sensor ready");
}

void loop() {
  VL53L0X_RangingMeasurementData_t measurement;
  sensor.rangingTest(&measurement, false);

  if (measurement.RangeStatus != 4) { // status 4 = out of range
    Serial.print("distance (mm): ");
    Serial.println(measurement.RangeMilliMeter);
  } else {
    Serial.println("out of range");
  }

  delay(100);
}
