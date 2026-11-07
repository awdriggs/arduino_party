# Motor Driver // Lab

## Introduction: What You'll Build

As you say the in the [DC Motor Lab](link) we can use the Arduino and a transistor to turn a motor on and off. By adding inputs we could change the speed. But it would be great to also control the direction that a dc motor moves or easily control multiple motors at the same time. To do this, we can add a Motor Driver board to our toolkit. This gives you full control over speed and direction for two motors at the same time. It handles all the heavy lifting so your Arduino doesn't have to. In this lab you'll wire up the driver board, run a motor forward and in reverse, and then use a potentiometer and button to control speed and direction in real time.

---

## What You'll Need

- Arduino Nano 33 IoT
- SparkFun Motor Driver - Dual TB6612FNG
- DC Motor (x2, or just one to start)
- 10k Potentiometer
- Pushbutton
- Solderless Breadboard
- Jumper Wires

> 📸 INSERT PHOTO: parts laid out flat, labeled

---

## Background: What is an H-Bridge?

To reverse a DC motor you need to flip the direction of current flowing through it. An H-bridge is a circuit that does exactly that. It can send current through the motor in either direction, giving you forward and reverse. The TB6612FNG has two H-bridges built in, one for each motor channel (A and B). It also has a PWM input for each channel so you can control speed at the same time.

> 📸 INSERT PHOTO: H-bridge diagram or the SparkFun board close-up

---

## Step 1: Wire Up the Motor Driver

Place the motor driver board on the breadboard. Make the following connections:

| TB6612FNG Pin | Arduino Nano |
|---|---|
| VM | VIN |
| VCC | 3.3V |
| GND | GND |
| STBY | D5 |
| AIN1 | D6 |
| AIN2 | D7 |
| PWMA | D9 |
| BIN1 | D4 |
| BIN2 | D3 |
| PWMB | D2 |

Connect Motor A wires to **A01** and **A02** on the driver board. Connect Motor B wires to **B01** and **B02**.

> 📸 INSERT PHOTO: breadboard wiring with motor driver, Nano, and motors

> 📸 INSERT PHOTO: Fritzing or wiring diagram

**Important:** VM is the motor power pin. Connect it to VIN, not 3.3V. The motors pull too much current for the onboard regulator. VCC is just for the logic on the board, that one gets 3.3V.

---

## Step 2: Forward and Reverse

Let's start simple. This sketch runs both motors forward for 2 seconds, stops, then runs them in reverse for 2 seconds.

```cpp
// Motor A
const int AIN1 = 2;
const int AIN2 = 4;
const int PWMA = 5;

// Motor B
const int BIN1 = 7;
const int BIN2 = 8;
const int PWMB = 6;

const int STBY = 9;

void setup() {
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); // take out of standby
}

void driveMotor(int ain1, int ain2, int pwmPin, int speed) {
  if (speed > 0) {
    digitalWrite(ain1, HIGH);
    digitalWrite(ain2, LOW);
  } else if (speed < 0) {
    digitalWrite(ain1, LOW);
    digitalWrite(ain2, HIGH);
    speed = -speed;
  } else {
    digitalWrite(ain1, LOW);
    digitalWrite(ain2, LOW);
  }
  analogWrite(pwmPin, speed);
}

void loop() {
  Serial.println("forward");
  driveMotor(AIN1, AIN2, PWMA, 200);
  driveMotor(BIN1, BIN2, PWMB, 200);
  delay(2000);

  Serial.println("stop");
  driveMotor(AIN1, AIN2, PWMA, 0);
  driveMotor(BIN1, BIN2, PWMB, 0);
  delay(1000);

  Serial.println("reverse");
  driveMotor(AIN1, AIN2, PWMA, -200);
  driveMotor(BIN1, BIN2, PWMB, -200);
  delay(2000);

  Serial.println("stop");
  driveMotor(AIN1, AIN2, PWMA, 0);
  driveMotor(BIN1, BIN2, PWMB, 0);
  delay(1000);
}
```

The `driveMotor` function takes a speed value from **-255 to 255**. Positive is forward, negative is reverse, zero is stop. AIN1/AIN2 set direction, PWMA sets speed.

**One thing to watch:** the STBY pin must be HIGH or the board won't do anything. If your motors aren't moving, check that first.

### What you should see

Both motors run forward, stop briefly, then reverse. You should also see "forward", "stop", "reverse" printing in the Serial Monitor.

> 📸 INSERT VIDEO/PHOTO: motors running forward and reverse

---

## Step 3: Speed Control with a Potentiometer

Now let's use a potentiometer to control the speed in real time. Add the pot to your breadboard. Center pin to A0, left pin to GND, right pin to 3.3V.

```cpp
// Motor A
const int AIN1 = 2;
const int AIN2 = 4;
const int PWMA = 5;

// Motor B
const int BIN1 = 7;
const int BIN2 = 8;
const int PWMB = 6;

const int STBY  = 9;
const int potPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);

  // set direction forward
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void loop() {
  int potValue = analogRead(potPin);
  int speed = map(potValue, 0, 1023, 0, 255);

  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);

  Serial.print("speed: ");
  Serial.println(speed);

  delay(50);
}
```

The pot reads a value from 0–1023. `map()` converts that to 0–255 for `analogWrite`. Turn the pot and the motors speed up and slow down.

> 📸 INSERT PHOTO: breadboard with potentiometer added

### What you should see

Turning the pot all the way down brings the motors to a stop. Turning it up runs them at full speed. Open the Serial Monitor to watch the speed value change as you turn.

---

## Step 4: Add a Button to Flip Direction

This sketch keeps the pot speed control and adds a button to toggle between forward and reverse. Wire the button with one leg to D3 and the other to GND. No resistor needed, we'll use the internal pullup.

```cpp
// Motor A
const int AIN1 = 2;
const int AIN2 = 4;
const int PWMA = 5;

// Motor B
const int BIN1 = 7;
const int BIN2 = 8;
const int PWMB = 6;

const int STBY   = 9;
const int potPin  = A0;
const int btnPin  = 3;

bool forward = true;
bool lastBtnState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);

  digitalWrite(STBY, HIGH);
}

void driveMotor(int ain1, int ain2, int pwmPin, int speed) {
  if (speed > 0) {
    digitalWrite(ain1, HIGH);
    digitalWrite(ain2, LOW);
  } else if (speed < 0) {
    digitalWrite(ain1, LOW);
    digitalWrite(ain2, HIGH);
    speed = -speed;
  } else {
    digitalWrite(ain1, LOW);
    digitalWrite(ain2, LOW);
  }
  analogWrite(pwmPin, speed);
}

void loop() {
  bool btnState = digitalRead(btnPin);
  if (btnState == LOW && lastBtnState == HIGH) {
    forward = !forward;
    Serial.println(forward ? "direction: forward" : "direction: reverse");
    delay(50);
  }
  lastBtnState = btnState;

  int potValue = analogRead(potPin);
  int speed = map(potValue, 0, 1023, 0, 255);
  int actualSpeed = forward ? speed : -speed;

  driveMotor(AIN1, AIN2, PWMA, actualSpeed);
  driveMotor(BIN1, BIN2, PWMB, actualSpeed);

  Serial.print("speed: ");
  Serial.print(speed);
  Serial.print("  direction: ");
  Serial.println(forward ? "forward" : "reverse");

  delay(50);
}
```

The button uses `INPUT_PULLUP`, so it reads HIGH normally and LOW when pressed. Each press flips the `forward` boolean, which changes the sign of the speed value sent to the motors.

> 📸 INSERT PHOTO: full breadboard with motor driver, pot, and button

### What you should see

Turn the pot to set speed, press the button to flip direction. The motors should respond instantly. Check the Serial Monitor to confirm direction and speed are updating correctly.

---

## If Something's Not Working

- **Nothing moving at all?** Check that STBY is wired to D9 and that `digitalWrite(STBY, HIGH)` is in your setup. This is the most common issue.
- **One motor not moving?** Double check the AIN/BIN and PWM pins for that channel.
- **Motors weak or stalling?** Make sure VM is connected to VIN, not 3.3V.
- **Button not toggling?** Open the Serial Monitor and check if direction is printing. If it is, the issue is the wiring to the motor, not the code.

---

## Remix it!

**Change the inputs!**
- Replace the pot with a force sensitive resistor to control speed with pressure.
- Use a distance sensor so the motors speed up when something gets close.
- Add a second button to lock the motors at a set speed.

**Change the outputs!**
- Try different motors: a fan, a gearbox motor, a small pump.
- Run the two motors at different speeds to create an asymmetric motion.

**Change the code!**
- Add a "brake" mode that stops the motors hard instead of just cutting power.
- Map the pot to only run between 30–100% speed so the motor never fully stops.

---

## What's Next?

With the motor driver you can control speed and direction. Next up: Stepper motors, precise control over rotations. 
