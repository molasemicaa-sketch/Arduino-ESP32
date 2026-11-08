#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN 16

CRGB leds[NUM_LEDS];
int cometPosition = 0;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  // Clear the strip
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // Set the comet's head
  leds[cometPosition] = CRGB::White;

  // Create the comet's tail
  for (int i = cometPosition - 1; i >= 0; i--) {
    leds[i] = CRGB(0, 0, 255 - (cometPosition - i) * 10); // Adjust color and fade
  }

  cometPosition++;
  if (cometPosition >= NUM_LEDS) {
    cometPosition = 0;
  }

  FastLED.show();
  delay(50); // Adjust delay for comet speed
}