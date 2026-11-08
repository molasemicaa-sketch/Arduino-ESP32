#include <FastLED.h>

#define LED_PIN     18      // Pin where the LED strip is connected (use any suitable GPIO pin on ESP32)
#define NUM_LEDS    60     // Number of LEDs in your strip
#define BRIGHTNESS  255    // Brightness of the LEDs

CRGB leds[NUM_LEDS];

void setup() {
  // Initialize FastLED for ESP32 with RGB color order
  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);  // Define LED strip type with RGB color order
  FastLED.setBrightness(BRIGHTNESS);  // Set brightness of the LEDs
}

void loop() {
  // Set all LEDs to deep purple using RGB values
 //fill_solid(leds, NUM_LEDS, CRGB(160, 32, 240));  // Deep purple RGB values
fill_solid(leds, NUM_LEDS, CRGB(128, 0, 128));



FastLED.show();  // Update the LED strip
  delay(100);  // Delay to prevent rapid changes
}
