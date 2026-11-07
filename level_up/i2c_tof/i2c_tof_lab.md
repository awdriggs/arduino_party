# I2C + Time of Flight // Lab

## Introduction: What You'll Build

So far, sensors have sent back a single analog value through one wire. I2C is a communication protocol that lets you send and receive much richer data over just two wires — and connect multiple sensors to those same two wires at the same time. In this lab you'll connect a Time of Flight distance sensor, read distance values in real time, and use that data to control the brightness of an LED.

---

## What You'll Need

- Arduino Nano 33 IoT
- Adafruit VL53L0X Time of Flight Distance Sensor
- LED
- 220 ohm resistor
- Solderless Breadboard
- Jumper Wires

> 📸 INSERT PHOTO: parts laid out flat, labeled

---

## Background: What is I2C?

I2C (pronounced "I squared C") is a way for microcontrollers to talk to sensors and other devices using just two wires: SDA (data) and SCL (clock). The clock wire keeps both sides in sync, and the data wire carries the actual information back and forth.

What makes I2C useful is that every device on the bus has its own address — a unique ID. That means you can chain multiple sensors onto the same two wires and talk to each one individually. The Arduino Nano 33 IoT has dedicated I2C pins: **SDA on A4** and **SCL on A5**.

> 📸 INSERT PHOTO or DIAGRAM: I2C bus diagram showing multiple devices on two wires

### What is a Time of Flight Sensor?

The VL53L0X measures distance by firing an invisible laser pulse and measuring how long it takes to bounce back. It returns distance in millimeters and works reliably from about 30mm to 1.2 meters. Unlike analog IR sensors, it gives you a clean digital reading over I2C with no calibration curves to worry about.

> 📸 INSERT PHOTO: VL53L0X sensor close-up

---

## Step 1: Wire Up the Sensor

| VL53L0X Pin | Arduino Nano |
|---|---|
| VIN | 3.3V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

> 📸 INSERT PHOTO: sensor wired to Nano on breadboard

Before uploading any code, install the **Adafruit VL53L0X** library. In the Arduino IDE go to Sketch > Include Library > Manage Libraries and search for "VL53L0X".

---

## Step 2: Print Distance to Serial

Upload this sketch and open the Serial Monitor. Move your hand toward and away from the sensor.

```cpp
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
```

The sensor returns a `measurement` object. `RangeMilliMeter` is the distance in millimeters. `RangeStatus == 4` means the sensor couldn't get a reading — too far, too close, or a reflective surface throwing it off.

### What you should see

Distance in millimeters printing to the Serial Monitor. Move your hand closer and the number drops, move it away and it climbs. Take note of the minimum and maximum values you get — you'll need them in the next step.

> 📸 INSERT VIDEO: serial monitor with live distance values

---

## Step 3: Distance Controls LED Brightness

Wire up an LED — long leg through a 220 ohm resistor to D5, short leg to GND.

> 📸 INSERT PHOTO: LED added to breadboard

Take the code from Step 2. Try converting the distance reading to control the brightness of an LED using PWM. The closer an object is to the sensor, the brighter the LED should be.

Use the min and max distance values you saw in the Serial Monitor to set your range.

### Hint 1: Reverse Mapping

> NOTION TOGGLE: Hint 1 — Reverse Mapping

The `map()` function normally goes low-to-high. To flip the relationship so closer = brighter, swap the output values so 255 comes first and 0 comes second.

```cpp
int brightness = map(distance, minDist, maxDist, 255, 0);
```

Also use `constrain()` to make sure the brightness never goes outside 0–255 if the sensor reads outside your expected range:

```cpp
brightness = constrain(brightness, 0, 255);
```

### Hint 2: Full Code

> NOTION TOGGLE: Hint 2 — Full Code

```cpp
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

const int ledPin = 5; // PWM pin

// adjust these to match the range you saw in the Serial Monitor
const int minDist = 30;
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
    analogWrite(ledPin, 0);
    Serial.println("out of range");
  }

  delay(50);
}
```

### What you should see

Move your hand toward the sensor and the LED brightens. Pull it away and it dims. At the max distance it turns off completely.

> 📸 INSERT VIDEO: hand moving toward sensor, LED brightening

---

## If Something's Not Working

- **"Sensor not found" in Serial Monitor?** Check SDA is on A4 and SCL is on A5. Make sure the library is installed.
- **Readings jumping around?** Try a slower `delay()` or point the sensor at a flat, non-reflective surface.
- **LED not responding?** Confirm D5 is a PWM pin and check the resistor and LED wiring.
- **Distance always "out of range"?** You're probably too close (under 30mm) or too far (over 1.2m).

---

## Remix it!

The distance value is just a number — you can map it to anything. Try swapping the LED for a different output:

- **Tone** — map distance to pitch, closer = higher sound. [Tone Lab](../tone/tone_lab.md)
- **Motor speed** — map distance to how fast a motor spins. [Motor Driver Lab](../../motors/motor_driver_dc/motor_driver_lab.md)
- **Servo position** — map distance to a servo angle. [Servo Lab](../../motors/servo/)

Or flip the relationship so farther = brighter, or set a threshold so the output only activates when something gets within 200mm.

---

## What's Next?

I2C opens up a whole category of sensors that would be hard or impossible to use over a single analog pin. A few worth exploring next:

- **[Adafruit MPR121 - 12-Key Capacitive Touch](https://www.adafruit.com/product/1982)** — add up to 12 touch pads to your project. Great for building custom interfaces and instruments.
- **[Adafruit STHS34PF80 IR Presence/Motion Sensor](https://www.adafruit.com/product/6426)** — detects presence and motion up to 4 meters away, a step up from a standard PIR sensor.
- **[Adafruit MAX44009 Lux Sensor](https://www.adafruit.com/product/6498)** — measures ambient light with a huge dynamic range, from near darkness to bright sunlight.
- **[Adafruit SGP30 Air Quality Sensor](https://www.adafruit.com/product/3709)** — measures CO2 and volatile organic compounds, useful for environment-responsive projects.
- **[Adafruit SSD1306 OLED Display](https://www.adafruit.com/product/931)** — a small screen you can draw text and graphics on, also over I2C.

All of these use the same two wires (SDA/SCL) and follow the same pattern: include the library, call `begin()`, read the data.
