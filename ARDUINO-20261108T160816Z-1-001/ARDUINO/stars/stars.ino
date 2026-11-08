#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN 16

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(100); // Adjust brightness as needed
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    // Randomly turn LEDs on and off
    if (random(10) == 0) {
      leds[i] = CRGB::White; // Adjust color as needed
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
  delay(100); // Adjust delay for twinkling speed
}