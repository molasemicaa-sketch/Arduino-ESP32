#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN 16

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  // Candle effect: Simulate a flickering flame
  for (int i = 0; i < NUM_LEDS; i++) {
    int brightness = random(0, 255); // Random brightness
    leds[i] = CRGB(brightness, brightness / 2, 0); // Adjust color as needed
  }

  FastLED.show();
  delay(100);
}