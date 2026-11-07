# Stepper Motor // Lab

## Introduction: What You'll Build

A stepper motor moves in precise, counted steps instead of spinning freely like a DC motor. That means you can tell it exactly how far to rotate and it will get there every time. In this lab you'll wire a stepper motor to the same motor driver board from the last lab. You'll start with two buttons to control direction, then add two more to control speed.

---

## What You'll Need

- Arduino Nano 33 IoT
- SparkFun Motor Driver - Dual TB6612FNG
- Adafruit Unipolar Stepper Motor (516 steps/rev)
- 4 Pushbuttons
- Solderless Breadboard
- Jumper Wires

> 📸 INSERT PHOTO: parts laid out flat, labeled

---

## Background: What is a Stepper Motor?

A stepper motor is a DC motor that moves in discrete steps instead of spinning continuously. Each step is a fixed angle, and by counting steps you know exactly where the motor is without any sensor. This makes them great for any project where precise, repeatable movement matters.

The motor in this lab has 516 steps per revolution thanks to an internal gear reduction. That means it moves in very small increments, which gives it good torque but limits its top speed. At 5V, keep it under 6 RPM or it will stall.

> 📸 INSERT PHOTO: stepper motor close-up

---

## Step 1: Wire Up the Motor Driver

The motor driver connections to the Arduino are the same as in the Motor Driver lab.

| TB6612FNG Pin | Arduino Nano |
|---|---|
| VM | VIN |
| VCC | 3.3V |
| GND | GND |
| STBY | D9 |
| AIN1 | D2 |
| AIN2 | D4 |
| PWMA | D5 |
| BIN1 | D7 |
| BIN2 | D8 |
| PWMB | D6 |

> 📸 INSERT PHOTO: motor driver on breadboard with Nano

---

## Step 2: Wire Up the Stepper Motor

This motor has a 5-wire connector. The red wire is the center tap — leave it unconnected. The other four wires connect to the motor driver outputs.

| Motor Wire | TB6612FNG Pin |
|---|---|
| Orange | AO1 |
| Pink | AO2 |
| Blue | BO1 |
| Yellow | BO2 |
| Red | Not connected |

> 📸 INSERT PHOTO: stepper motor wired to driver board

> 📸 INSERT PHOTO: Fritzing or full wiring diagram

---

## Step 3: Two Button Direction Control

Start with just two buttons — one for forward, one for backward. Wire each button with one leg on its pin and the other to GND. No resistors needed, we'll use the internal pullups.

| Button | Pin |
|---|---|
| Forward | D3 |
| Backward | D10 |

> 📸 INSERT PHOTO: breadboard with two buttons added

```cpp
#include <Stepper.h>

const int stepsPerRevolution = 516; // 516 steps = one full revolution with gearing
Stepper myStepper(stepsPerRevolution, 2, 4, 7, 8); // coil A: pins 2,4 | coil B: pins 7,8

const int PWMA = 5;
const int PWMB = 6;
const int STBY = 9;

const int btnForward = 3;
const int btnBack    = 10;

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

  myStepper.setSpeed(4); // RPM
}

void loop() {
  if (digitalRead(btnForward) == LOW) {
    myStepper.step(1);
    Serial.println("forward");
  } else if (digitalRead(btnBack) == LOW) {
    myStepper.step(-1);
    Serial.println("back");
  }
}
```

Hold a button and the motor turns. Release it and it stops. `myStepper.step(1)` moves one step forward, `myStepper.step(-1)` moves one step backward. Because we call it one step at a time in the loop, the motor responds immediately to the button.

### What you should see

Hold forward and the motor turns one direction. Hold backward and it reverses. Open the Serial Monitor to confirm the buttons are registering.

> 📸 INSERT VIDEO/PHOTO: motor responding to buttons

---

## Step 4: Add Speed Control

Now add two more buttons to control speed. Keep everything from Step 3 and just add the two new buttons on D11 and D12.

| Button | Pin | Action |
|---|---|---|
| Button 1 | D3 | Forward fast |
| Button 2 | D10 | Forward slow |
| Button 3 | D11 | Backward fast |
| Button 4 | D12 | Backward slow |

> 📸 INSERT PHOTO: breadboard with all four buttons

```cpp
#include <Stepper.h>

const int stepsPerRevolution = 516; // 516 steps = one full revolution with gearing
Stepper myStepper(stepsPerRevolution, 2, 4, 7, 8); // coil A: pins 2,4 | coil B: pins 7,8

const int PWMA = 5;
const int PWMB = 6;
const int STBY = 9;

const int btnForwardFast = 3;
const int btnForwardSlow = 10;
const int btnBackFast    = 11;
const int btnBackSlow    = 12;

const int FAST_SPEED = 6; // RPM - max safe for this motor at 5V
const int SLOW_SPEED = 2; // RPM

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
  pinMode(btnForwardFast, INPUT_PULLUP);
  pinMode(btnForwardSlow, INPUT_PULLUP);
  pinMode(btnBackFast,    INPUT_PULLUP);
  pinMode(btnBackSlow,    INPUT_PULLUP);
}

void loop() {
  // hold a button to keep stepping in that direction and speed
  if (digitalRead(btnForwardFast) == LOW) {
    myStepper.setSpeed(FAST_SPEED);
    myStepper.step(1);
    Serial.println("forward fast");
  } else if (digitalRead(btnForwardSlow) == LOW) {
    myStepper.setSpeed(SLOW_SPEED);
    myStepper.step(1);
    Serial.println("forward slow");
  } else if (digitalRead(btnBackFast) == LOW) {
    myStepper.setSpeed(FAST_SPEED);
    myStepper.step(-1);
    Serial.println("back fast");
  } else if (digitalRead(btnBackSlow) == LOW) {
    myStepper.setSpeed(SLOW_SPEED);
    myStepper.step(-1);
    Serial.println("back slow");
  }
}
```

`myStepper.setSpeed()` changes the RPM before each step. The difference between 2 and 6 RPM is subtle but noticeable, especially with something attached to the shaft.

### What you should see

Four distinct behaviors across the four buttons. The slow buttons should feel noticeably more deliberate.

> 📸 INSERT VIDEO/PHOTO: all four buttons in action

---

## If Something's Not Working

- **Motor not moving at all?** Check STBY is on D9 and `digitalWrite(STBY, HIGH)` is in setup.
- **Motor humming but not turning?** It's stalling. Make sure VM is on VIN not 3.3V, and don't go above 6 RPM.
- **Motor moving the wrong direction?** Swap the orange and pink wires, or swap blue and yellow.
- **Buttons not responding?** Open the Serial Monitor and check for output when pressing. If nothing prints, check the button wiring.

---

## Remix it!

**Change the inputs!**
- Replace the buttons with a potentiometer. Map one half to forward, the other half to reverse, with speed increasing as you turn further from center.
- Use a distance sensor to drive the motor based on how close something is.

**Change the code!**
- Add a step counter and print the total to Serial. How many steps is one full revolution?
- Make the motor rotate exactly one full revolution when you press a button, then stop.

**Change the outputs!**
- Attach a pointer, disc, or cam to the shaft. Steppers are great for anything that needs to land in the same place every time.

---

## What's Next?

You've now worked with three types of motors: DC, servo, and stepper. Each one trades off speed, precision, and complexity in different ways. The right motor for a project depends on what kind of movement you need and how much control matters.
