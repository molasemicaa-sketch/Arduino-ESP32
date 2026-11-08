#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN 16

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  // Cycle through different neon colors
  static uint8_t hue = 0;
  hue++;
  hue %= 256;

  // Create a pulsating effect
  static uint8_t brightness = 0;
  brightness += 5;
  if (brightness > 255) {
    brightness = 0;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 255, brightness);
  }

  FastLED.show();
  delay(20);
}