#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN 16

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    int blue = random(0, 255);
    int cyan = random(0, 255);
    leds[i] = CRGB(0, cyan, blue); // Blue and Cyan color
  }

  FastLED.show();
  delay(100);
}