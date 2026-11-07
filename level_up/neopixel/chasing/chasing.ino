#include <Adafruit_NeoPixel.h>

const int pixelPin  = 6;
const int numPixels = 16;

Adafruit_NeoPixel strip(numPixels, pixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(100);
  strip.show(); // initialize all pixels to off
}

void loop() {
  for (int i = 0; i < numPixels; i++) {
    strip.clear();                              // turn all pixels off
    strip.setPixelColor(i, strip.Color(0, 0, 255)); // light up current pixel
    strip.show();
    delay(100);
  }
}
