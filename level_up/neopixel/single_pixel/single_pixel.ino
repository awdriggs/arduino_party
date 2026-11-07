#include <Adafruit_NeoPixel.h>

const int pixelPin = 6;
const int numPixels = 1;

Adafruit_NeoPixel pixel(numPixels, pixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Serial.println("starting...");
  pixel.begin();
  pixel.setBrightness(100); // 0-255, keep it reasonable to limit current draw
  pixel.show();             // initialize to off
}

void loop() {
  Serial.println("red");
  pixel.setPixelColor(0, pixel.Color(255, 0, 0));
  pixel.show();
  delay(1000);

  Serial.println("green");
  pixel.setPixelColor(0, pixel.Color(0, 255, 0));
  pixel.show();
  delay(1000);

  Serial.println("blue");
  pixel.setPixelColor(0, pixel.Color(0, 0, 255));
  pixel.show();
  delay(1000);

  Serial.println("white");
  pixel.setPixelColor(0, pixel.Color(255, 255, 255));
  pixel.show();
  delay(1000);

  Serial.println("off");
  pixel.setPixelColor(0, pixel.Color(0, 0, 0));
  pixel.show();
  delay(1000);
}
