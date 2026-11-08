#include <Adafruit_NeoPixel.h>
#include <WiFi.h>              // Necessary for ESP32 compatibility

#define LED_PIN     18         // Change to the GPIO pin you're using for the NeoPixel data line
#define NUM_LEDS    30         // Number of LEDs in your NeoPixel strip
#define BRIGHTNESS  50         // Brightness (0 to 255)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  strip.begin();               // Initialize the strip
  strip.setBrightness(BRIGHTNESS);
  strip.show();                // Initialize all pixels to 'off'
}

void loop() {
    // Red color wipe
  colorWipe(strip.Color(160, 32, 240), 50);     
  colorWipe(strip.Color(128,0,128), 50);    // Green color wipe
  colorWipe(strip.Color(0, 0, 255), 50);
  colorWipe(strip.Color(128,0,128), 50);  // Pink
  colorWipe(strip.Color(0, 0, 255), 50);       // Blue
  colorWipe(strip.Color(0, 255, 255), 50);    // Cyan
  colorWipe(strip.Color(0, 0, 128), 50);      // Navy Blue
  colorWipe(strip.Color(0, 255, 0), 50);       // Green
  colorWipe(strip.Color(139, 69, 19), 50);    // Brown
 colorWipe(strip.Color(162, 0, 255), 50);// Purple //162, 0, 255
   // Rainbow effect
}

// Function to fill the strip with a single color
void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for(int i = 0; i < NUM_LEDS; i++) {
      int pixelHue = firstPixelHue + (i * 65536L / NUM_LEDS);
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
  
}
