# Solenoid // Lab

## Introduction: What You'll Build

The Arduino runs on 3.3V and can only directly control small, low-power components. But with a transistor acting as a switch, you can use the Arduino to control devices that need much higher voltages — like a 12V solenoid powered by a wall adapter. In this lab you'll wire up a solenoid so that pressing a button fires it.

---

## What You'll Need

- Arduino Nano 33 IoT
- 12V Solenoid
- 12V DC Wall Wart power supply
- 2N2222 NPN Transistor
- 1N4001 Flyback Diode (or any general purpose diode)
- 1k ohm resistor
- Pushbutton
- Solderless Breadboard
- Jumper Wires

> 📸 INSERT PHOTO: parts laid out flat, labeled

---

## Background: What is a Solenoid?

A solenoid is an electromechanical actuator — when you send current through it, a metal plunger shoots in or out. Cut the power and a spring snaps it back. They're fast, reliable, and loud, which makes them great for anything that needs a sudden physical action: door locks, pinball bumpers, pneumatic valves, cash drawers, typewriter keys, and percussion instruments. Unlike a motor that spins, a solenoid just punches.

> 📸 INSERT PHOTO: solenoid close-up, maybe showing plunger extended and retracted

### What is a Wall Wart?

A wall wart is a plug-in power adapter — the chunky brick that plugs directly into the wall and converts AC mains power to a lower DC voltage. The solenoid in this lab needs 12V, which is more than a USB port or the Arduino can supply. The wall wart provides that 12V on a separate power rail. The Arduino and the wall wart share a common ground so they can work together, but the solenoid current never flows through the Arduino.

> 📸 INSERT PHOTO: wall wart with DC barrel jack, label pointing out voltage and polarity

---

## Step 1: Understand the Circuit

The Arduino pin alone can't drive a 12V solenoid — it only outputs 3.3V at a few milliamps. The 2N2222 transistor solves this the same way it did in the DC motor labs. The Arduino pin controls the base of the transistor with a small current, and the transistor switches the much larger 12V solenoid current on and off.

The flyback diode is important here. When the solenoid turns off, the collapsing magnetic field generates a voltage spike that can damage the transistor and the Arduino. The diode gives that spike a safe path to dissipate.

> 📸 INSERT DIAGRAM: circuit diagram showing wall wart, solenoid, transistor, diode, and Arduino

---

## Step 2: Wire It Up

**Solenoid circuit (12V side):**
- Wall wart positive → solenoid positive terminal
- Solenoid negative terminal → transistor collector
- Transistor emitter → GND (breadboard ground rail)
- Flyback diode across the solenoid: cathode (striped end) to positive terminal, anode to negative terminal

**Arduino to transistor:**
- D2 → 1k ohm resistor → transistor base

**Shared ground:**
- Wall wart GND → breadboard GND rail
- Arduino GND → breadboard GND rail

**Button:**
- One leg → D3
- Other leg → GND

> 📸 INSERT PHOTO: full breadboard wiring
> 📸 INSERT PHOTO: Fritzing or wiring diagram

**Important:** The wall wart and Arduino must share a common ground or the transistor won't switch correctly. Do not connect the 12V rail to anything on the Arduino.

---

## Step 3: The Code

```cpp
const int solenoidPin = 2;
const int btnPin      = 3;

void setup() {
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP); // button uses internal pullup, no resistor needed
}

void loop() {
  if (digitalRead(btnPin) == LOW) {
    digitalWrite(solenoidPin, HIGH); // open solenoid
    Serial.println("ON");
  } else {
    digitalWrite(solenoidPin, LOW);  // close solenoid
    Serial.println("OFF");
  }
}
```

Hold the button and the solenoid fires. Release it and the plunger snaps back.

### What you should see

A satisfying clunk every time you press the button. Open the Serial Monitor to confirm the button is registering.

> 📸 INSERT VIDEO: solenoid firing on button press

---

## If Something's Not Working

- **Nothing happens?** Check that the wall wart GND and the Arduino GND are connected together on the breadboard.
- **Solenoid fires on its own without pressing the button?** The transistor may be wired incorrectly. Double check emitter to GND, collector to solenoid, base through the 1k resistor to D2.
- **Arduino resetting when solenoid fires?** The flyback diode may be missing or wired backwards. The striped end goes to the positive side of the solenoid.
- **Button not registering?** Open Serial Monitor and confirm you see ON/OFF printing.

---

## Remix it!

**Change the trigger!**
- Replace the button with a PIR motion sensor to fire the solenoid when someone walks by.
- Use the Time of Flight sensor to fire when something gets within a set distance. [I2C Lab](../level_up/i2c_tof/i2c_tof_lab.md)
- Use a pressure sensor so it fires based on how hard you squeeze.

**Change the timing!**
- Add a `delay()` after firing to create a minimum time between shots.
- Fire in a burst — on, off, on, off rapidly — to create a stuttering effect.
- Use `millis()` instead of `delay()` so the button stays responsive while timing the firing.

---

## What's Next?

The transistor + high voltage pattern you used here applies to anything that needs more power than the Arduino can provide directly: 12V fans, LED strips on external power, relays, pumps, and valves. Once you understand this circuit, you can control almost any DC device regardless of its voltage or current requirements.
