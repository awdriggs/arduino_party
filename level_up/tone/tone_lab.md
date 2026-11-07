# Tone Output // Lab

## Introduction: What You'll Build

The Arduino can generate sound by rapidly vibrating a speaker at a set frequency. Higher frequency = higher pitch, lower frequency = lower pitch. In this lab you'll start by playing a famous 5-note sequence, then use a pressure sensor to control pitch in real time, and finally build a simple three-note instrument you can play with your hands.

---

## What You'll Need

- Arduino Nano 33 IoT
- 8 ohm speaker (or piezo buzzer)
- 100 ohm resistor
- Force Sensitive Resistor / FSR (x3 for the instrument step)
- 10k ohm resistor (x3, one per FSR)
- Solderless Breadboard
- Jumper Wires

> 📸 INSERT PHOTO: parts laid out flat, labeled

---

## Background: How Does tone() Work?

Sound is vibration. A speaker cone moves back and forth, pushing air, and that moving air reaches your ears as sound. The speed of that vibration is the frequency, measured in Hertz (Hz). 440 Hz is concert A. Middle C is 262 Hz.

The Arduino `tone()` function handles all of that for you. You give it a pin, a frequency, and an optional duration, and it drives the speaker at that frequency. `noTone()` stops it.

```cpp
tone(pin, frequency);            // play until noTone() is called
tone(pin, frequency, duration);  // play for a set number of milliseconds
noTone(pin);                     // stop playing
```

The speaker needs a resistor in series (100 ohm) to limit current from the pin.

---

## Step 1: Wire Up the Speaker

- Speaker positive leg → 100 ohm resistor → D8
- Speaker negative leg → GND

> 📸 INSERT PHOTO: speaker wired to breadboard and Nano

---

## Step 2: Close Encounters

Let's play something. The five-note motif from Close Encounters of the Third Kind is one of the most recognizable sequences in music. The notes are D, E, C, C (lower octave), G.

```cpp
const int speakerPin = 8;

int notes[]     = {587, 659, 523, 262, 392};
int durations[] = {500, 500, 500, 500, 1000};

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    tone(speakerPin, notes[i], durations[i]);
    delay(durations[i] + 50); // small gap between notes
  }
  delay(2000); // pause before repeating
}
```

The notes and durations are stored in arrays. The loop steps through each one, plays it for the set duration, then moves to the next. Try changing the values in the `durations` array to play with the rhythm.

### What you should see

The sequence plays, pauses for two seconds, then repeats.

> 📸 INSERT VIDEO: sequence playing

---

## Step 3: FSR Pitch Control

Now add an FSR to control pitch in real time. Wire the FSR as a voltage divider — one leg to 3.3V, the other leg to A0 and also to a 10k resistor that goes to GND.

> 📸 INSERT PHOTO: FSR voltage divider wiring

Before writing the pitch control code, upload this calibration sketch and open the Serial Monitor. Press the FSR from a light touch to a hard press and note the range of values you get. You'll use those to tune the `map()` call in the next sketch.

```cpp
const int fsrPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(fsrPin));
  delay(50);
}
```

Once you know your range, update the first two values in `map()` to match what you saw.

```cpp
const int speakerPin = 8;
const int fsrPin     = A0;

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  int fsrReading = analogRead(fsrPin);
  Serial.println(fsrReading);

  if (fsrReading > 50) { // only play when the sensor is pressed
    int frequency = map(fsrReading, 50, 1023, 100, 2000);
    tone(speakerPin, frequency);
  } else {
    noTone(speakerPin);
  }

  delay(10);
}
```

Press lightly for a low pitch, press hard for a high pitch. Releasing stops the sound.

### What you should see

Pressing the FSR makes a sound. Pressing harder raises the pitch.

> 📸 INSERT VIDEO: hand pressing FSR, pitch changing

---

## Step 4: Three-Note Instrument

Add two more FSRs on A1 and A2. Each one is wired the same way as the first. Each sensor triggers a different predefined note — together they form a C major chord.

> 📸 INSERT PHOTO: three FSRs wired on breadboard

```cpp
const int speakerPin = 8;

const int fsr1 = A0;
const int fsr2 = A1;
const int fsr3 = A2;

// C major chord
const int noteC = 262;
const int noteE = 330;
const int noteG = 392;

const int threshold = 50;

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  if (analogRead(fsr1) > threshold) {
    tone(speakerPin, noteC);
    Serial.println("C");
  } else if (analogRead(fsr2) > threshold) {
    tone(speakerPin, noteE);
    Serial.println("E");
  } else if (analogRead(fsr3) > threshold) {
    tone(speakerPin, noteG);
    Serial.println("G");
  } else {
    noTone(speakerPin);
  }

  delay(10);
}
```

Press any sensor to play its note. If sensors are triggering on their own, raise the `threshold` value.

### What you should see

Each FSR plays a different note. Press them in different orders and rhythms to make something musical.

> 📸 INSERT VIDEO: three-note instrument being played

---

## If Something's Not Working

- **No sound at all?** Check the resistor and speaker wiring. Make sure the speaker is on D8.
- **Constant tone that won't stop?** Raise the `threshold` value.
- **FSR not responding?** Open the Serial Monitor and watch the raw values. If they're not changing when you press, check the voltage divider wiring.
- **All three FSRs play the same note?** Make sure each FSR is on a different analog pin (A0, A1, A2).

---

## Remix it!

**Change the notes!**
- Swap the C major notes for a minor chord (C, Eb, G = 262, 311, 392) for a darker sound.
- Assign each FSR to one of the Close Encounters notes.

**Change the inputs!**
- Replace an FSR with a potentiometer and use it to shift all three notes up or down in pitch.
- Use a light sensor instead of an FSR so the instrument responds to shadow and light.

**Change the code!**
- Add a button that plays back the Close Encounters sequence when pressed.
- Store a melody as an array and play it when you press a button.
