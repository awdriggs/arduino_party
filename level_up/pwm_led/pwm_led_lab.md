# PWM // Lab

## Introduction: What You'll Build

So far you have used `digitalWrite` to turn things on and off. But what if you want something in between? Pulse Width Modulation (PWM) lets you fake an analog output by switching a pin on and off very quickly. The result is a controllable average voltage that can dim an LED, control motor speed, or drive a servo. In this lab you'll use PWM to control the brightness of an LED — first with an automatic fade, then with a potentiometer.

---

## What You'll Need

- Arduino Nano 33 IoT
- LED (any color)
- 220 ohm resistor
- 10k Potentiometer
- Solderless Breadboard
- Jumper Wires

> 📸 INSERT PHOTO: parts laid out flat, labeled

---

## Background: What is PWM?

PWM works by switching a pin on and off hundreds of times per second. The duty cycle is the percentage of each cycle that the signal is on. A 50% duty cycle means the pin is on half the time, which delivers half the average voltage. A 100% duty cycle is fully on, 0% is fully off.

Your eyes can't see the switching — they just perceive the average brightness. That's what makes it look like a smooth dim instead of a flicker.

On the Arduino Nano 33 IoT, PWM pins are marked with a tilde (~) on the board. `analogWrite()` takes a value from 0 to 255, where 0 is 0% duty cycle and 255 is 100%.

> 📸 INSERT PHOTO or DIAGRAM: PWM duty cycle illustration showing 25%, 50%, 75%

---

## Step 1: Wire Up the LED

Connect the LED with a 220 ohm resistor in series to protect it. The long leg of the LED is positive.

- Long leg (positive) → 220 ohm resistor → D5
- Short leg (negative) → GND

> 📸 INSERT PHOTO: LED and resistor on breadboard wired to Nano

**Why D5?** It's a PWM pin. If you use a non-PWM pin, `analogWrite` won't work and the LED will just turn on at full brightness.

---

## Step 2: Fade Up and Down

This sketch automatically fades the LED from off to full brightness, then back down, in a loop.

```cpp
const int ledPin = 5; // must be a PWM pin (~)

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // fade up
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);
    Serial.println(brightness);
    delay(8);
  }

  // fade down
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    Serial.println(brightness);
    delay(8);
  }
}
```

The loop counts from 0 to 255 and back down, writing each value to the LED with `analogWrite`. The `delay(8)` slows it down enough to see the fade. Open the Serial Monitor and watch the brightness value climb and fall in real time.

### What you should see

The LED breathes — smoothly fading up and then back down in a loop.

> 📸 INSERT VIDEO: LED fading up and down

---

## Step 3: Control Brightness with a Potentiometer

Now let's put you in control. Add the potentiometer to your breadboard — center pin to A0, left pin to GND, right pin to 3.3V. The LED stays wired the same way.

> 📸 INSERT PHOTO: breadboard with pot added

```cpp
const int ledPin = 5; // must be a PWM pin (~)
const int potPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue   = analogRead(potPin);
  int brightness = map(potValue, 0, 1023, 0, 255);

  analogWrite(ledPin, brightness);

  Serial.print("pot: ");
  Serial.print(potValue);
  Serial.print("  brightness: ");
  Serial.println(brightness);

  delay(50);
}
```

`analogRead` returns a value from 0 to 1023. `map` converts that range to 0 to 255 for `analogWrite`. Turn the pot and the LED follows.

### What you should see

Turning the pot dims and brightens the LED. Open the Serial Monitor to see both the raw pot reading and the mapped brightness value side by side.

> 📸 INSERT VIDEO: hand turning pot, LED responding

---

## If Something's Not Working

- **LED always full brightness?** You're probably on a non-PWM pin. Check that your pin has a ~ on the board and matches `ledPin` in the code.
- **LED not turning on at all?** Check the resistor and make sure the long leg of the LED is on the signal side, not GND.
- **Pot not doing anything?** Make sure the center pin is on A0 and the outer pins are on 3.3V and GND.

---

## Remix it!

**Change the code!**
- Change `delay(8)` in the fade sketch to something faster or slower. How does that change the feel?
- Map the pot to only go between 50 and 255 so the LED never fully turns off.
- Add a button that freezes the brightness wherever the pot is sitting when you press it.

**Change the outputs!**
- Swap the LED for an RGB LED and control each channel separately with three pots.
- Use the same `analogWrite` pattern to control a buzzer and change its volume.

---

## What's Next?

You've been using PWM already without thinking about it — `analogWrite` in the motor labs is the same thing. Now that you understand what's happening under the hood, you can apply it anywhere you need a value between fully on and fully off.
