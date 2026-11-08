#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN 18

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void setWaveEffect() {
  for (int i = 0; i < NUM_LEDS; i++) {
    // Calculate the phase shift for each pixel
    float phase = i * 2 * PI / NUM_LEDS;

    // Calculate brightness based on a sine wave
    int brightness = 128 + 127 * sin(millis() / 100.0 + phase);
    brightness = constrain(brightness, 0, 255);

    // Set pixel color with calculated brightness (using cyan and blue)
    leds[i] = CRGB(0, brightness / 2, brightness);
    
  }
  FastLED.show();
}

void loop() {
  setWaveEffect();
  delay(0.5); // Adjust delay for wave speed
}