#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN 16

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void aurora() {
  for (int i = 0; i < NUM_LEDS; i++) {
    // Generate random hue and saturation
    int hue = random(0, 255);
    int sat = random(100, 255);

    // Gradually fade the brightness as we move along the strip
    int brightness = 255 - i * 8;
    brightness = constrain(brightness, 0, 255);

    leds[i] = CHSV(hue, sat, brightness);
  }

  FastLED.show();
  delay(50);
}