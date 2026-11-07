# NeoPixels // Lab

## Introduction: What You'll Build

NeoPixels are RGB LEDs with a tiny control chip built right in. Instead of needing three separate PWM pins to mix red, green, and blue, you control them all — and as many as you want in a chain — using a single data pin. In this lab you'll start with one pixel and mix colors with code, then chain five together and make them chase.

---

## What You'll Need

- Arduino Nano 33 IoT
- Adafruit NeoPixel Breadboard LEDs - Pack of 5
- 300 ohm resistor (for data line)
- Solderless Breadboard
- Jumper Wires

> 📸 INSERT PHOTO: parts laid out flat, labeled

---

## Background: How Do NeoPixels Work?

A standard RGB LED needs three separate pins to control it — one each for red, green, and blue. NeoPixels have a tiny chip inside that handles that for you. You send color data down a single wire, and the chip sets the right brightness for each channel. What makes them powerful is that they're chainable — the output of one pixel connects to the input of the next, and you can control a whole string from a single Arduino pin.

Colors are set using three values: red, green, and blue, each from 0 to 255. Mix them to make any color you want.

> 📸 INSERT PHOTO: single NeoPixel close-up showing the four pins

**A few things to keep in mind:**
- Always put a 300 ohm resistor on the data line between the Arduino and the first pixel.
- NeoPixels can draw a lot of current at full white. Use `setBrightness()` to keep things reasonable, especially on a breadboard.
- Always call `pixel.show()` after setting colors or nothing will update.

---

## Step 1: Wire Up a Single NeoPixel

Each NeoPixel has four pins: 5V, GND, Data In, and Data Out.

- **5V** → VIN
- **GND** → GND
- **Data In** → 300 ohm resistor → D6
- **Data Out** → leave unconnected for now

> 📸 INSERT PHOTO: single NeoPixel wired on breadboard

Install the **Adafruit NeoPixel** library before uploading. In the Arduino IDE go to Sketch > Include Library > Manage Libraries and search for "Adafruit NeoPixel".

---

## Step 2: Control a Single Pixel

This sketch cycles through red, green, blue, white, and off.

```cpp
#include <Adafruit_NeoPixel.h>

const int pixelPin  = 6;
const int numPixels = 1;

Adafruit_NeoPixel pixel(numPixels, pixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  pixel.begin();
  pixel.setBrightness(100); // 0-255, keep it reasonable to limit current draw
  pixel.show();             // initialize to off
}

void loop() {
  // red
  pixel.setPixelColor(0, pixel.Color(255, 0, 0));
  pixel.show();
  delay(1000);

  // green
  pixel.setPixelColor(0, pixel.Color(0, 255, 0));
  pixel.show();
  delay(1000);

  // blue
  pixel.setPixelColor(0, pixel.Color(0, 0, 255));
  pixel.show();
  delay(1000);

  // white (all channels on)
  pixel.setPixelColor(0, pixel.Color(255, 255, 255));
  pixel.show();
  delay(1000);

  // off
  pixel.setPixelColor(0, pixel.Color(0, 0, 0));
  pixel.show();
  delay(1000);
}
```

`pixel.Color(r, g, b)` takes three values from 0 to 255. `setPixelColor(0, ...)` sets pixel 0 — the first one. `show()` sends the data to the pixel.

Try mixing your own colors by changing the three values in `pixel.Color()`. Yellow is (255, 255, 0). Purple is (128, 0, 128).

### What you should see

The pixel steps through red, green, blue, white, then off, repeating.

> 📸 INSERT VIDEO: single pixel cycling through colors

---

## Step 3: Chain Five Pixels — Chasing Pattern

Connect the remaining four pixels in a chain. The **Data Out** of each pixel connects to the **Data In** of the next. Power and ground run in parallel to all five.

> 📸 INSERT PHOTO: five pixels chained on breadboard
> 📸 INSERT PHOTO: wiring diagram showing chain connection

Change `numPixels` to 5 and upload this sketch:

```cpp
#include <Adafruit_NeoPixel.h>

const int pixelPin  = 6;
const int numPixels = 5;

Adafruit_NeoPixel strip(numPixels, pixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(100);
  strip.show(); // initialize all pixels to off
}

void loop() {
  for (int i = 0; i < numPixels; i++) {
    strip.clear();                                  // turn all pixels off
    strip.setPixelColor(i, strip.Color(0, 0, 255)); // light up current pixel
    strip.show();
    delay(100);
  }
}
```

The loop steps through each pixel index, clears everything, turns on just that one pixel, then moves to the next. Change the `delay()` to speed up or slow down the chase. Change the color in `strip.Color()` to whatever you like.

### What you should see

A single blue light chases from one end of the strip to the other, then repeats.

> 📸 INSERT VIDEO: chasing pattern running

---

## If Something's Not Working

- **Pixel not lighting up?** Check the 300 ohm resistor is on the data line, not the power line. Make sure you're calling `pixel.show()`.
- **Wrong colors?** Some pixels use GRB order instead of RGB. The library constructor handles this — make sure you have `NEO_GRB` set.
- **Only the first pixel works in the chain?** Check that Data Out from pixel 1 is connected to Data In on pixel 2, and so on.
- **Pixels flickering or dim?** Make sure 5V is on VIN, not 3.3V.

---

## Remix it!

**Ping pong the chase**

Instead of looping in one direction, make the light bounce back and forth. Count up to the last pixel then back down to the first, repeating.

**Control RGB with three FSRs**

Use three force sensitive resistors — one for red, one for green, one for blue — to mix the color of your pixel by hand. It's the same pattern as the [Tone Instrument Lab](../tone/tone_lab.md), just with color channels instead of notes. Map each FSR reading (0–1023) to a color channel value (0–255) and pass all three into `pixel.Color()`.

**Control blue channel with distance**

Use the Time of Flight sensor from the [I2C Lab](../i2c_tof/i2c_tof_lab.md) to control the blue channel. Move your hand close and the pixel goes bright blue. Pull away and it fades out. Try doing the same with red and green using other sensors.

**Change the chase**

- Add a trail — keep the previous pixel on at half brightness instead of clearing it immediately.
- Use a pot to control the speed of the chase.

---

## What's Next?

The same library and the same code patterns work across all NeoPixel form factors. Once you know how to control a strip of five, you can control any of these:

- **[NeoPixel Strips](https://www.adafruit.com/category/168)** — flexible strips in various densities (30, 60, 144 LEDs per meter). Cut to any length.
- **[NeoPixel Rings](https://www.adafruit.com/category/187)** — circular arrangements in sizes from 12 to 60 pixels. Great for clocks, indicators, and wearables.
- **[NeoPixel Matrices](https://www.adafruit.com/category/186)** — grids of pixels for displaying text, animations, and simple graphics.
- **[NeoPixel Jewels](https://www.adafruit.com/product/2226)** — a tight cluster of 7 pixels on a small board, good for compact projects.

The only thing that changes between them is `numPixels`. The rest of the code stays the same.
