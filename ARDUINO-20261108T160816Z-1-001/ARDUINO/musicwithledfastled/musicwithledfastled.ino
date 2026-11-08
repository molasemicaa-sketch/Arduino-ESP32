#include <FastLED.h>  
#include "BluetoothSerial.h"   // Bluetooth Serial library for LED commands
#include "BluetoothA2DPSink.h" // Bluetooth audio sink library for music playback

#define PIN 18           // Pin connected to the LED strip
#define NUMPIXELS 30     // Number of pixels in the strip

// Define the LED array
CRGB leds[NUMPIXELS];

BluetoothSerial SerialBT;        // Bluetooth Serial object for LED control
BluetoothA2DPSink a2dp_sink;     // Bluetooth audio sink object for music playback

void setup() {
  // Initialize serial communications
  Serial.begin(115200);

  // Separate names for LED control and audio streaming
  const char* ledControlName = "FOM Speaker Control";
  const char* audioDeviceName = "FOM Speaker Audio";

  // Initialize Bluetooth Serial for LED commands
  SerialBT.begin(ledControlName);

  // Initialize the LED strip
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUMPIXELS).setCorrection(TypicalLEDStrip);

  // Adjust brightness globally (range: 0-255)
  FastLED.setBrightness(128); // Set brightness to 50%

  // Set default LED color
  setColor(CRGB::White);
  FastLED.show();

  // Initialize A2DP sink for music playback
  a2dp_sink.start(audioDeviceName);

  Serial.println("ESP32 Speaker Ready with LED Control!");
}

void loop() {
  // Handle LED control commands via Bluetooth Serial
  if (SerialBT.available()) {
    String data = SerialBT.readStringUntil('\n'); // Read until a newline character
    Serial.println(data); // Print the received data for debugging

    // Check if the received data is an RGB command
    if (data.indexOf(",") != -1) {
      // Parse the RGB values
      int r, g, b;
      sscanf(data.c_str(), "%d,%d,%d", &r, &g, &b); // Extract RGB values from the string

      // Set the LEDs to the received color
      setColor(CRGB(r, g, b));
    } else {
      // Handle single-character commands
      char command = data[0];

      switch (command) {
        case '1': setColor(CRGB::White); break;
        case '0': setColor(CRGB::Black); break;
        case 'a': setColor(CRGB::Yellow); break;
        case 'b': setColor(CRGB(255, 165, 0)); break; // Orange
        case 'c': setColor(CRGB(255, 18, 22)); break; // Pink
        case 'd': setColor(CRGB::Blue); break;
        case 'e': setColor(CRGB::Cyan); break;
        case 'f': setColor(CRGB::Navy); break;
        case 'g': setColor(CRGB::Green); break;
        case 'h': setColor(CRGB(139, 69, 19)); break; // Brown
        case 'i': setColor(CRGB::Purple); break;
        case 'j': setColor(CRGB(141, 255, 255)); break; // Light blue
        case 'k': setColor(CRGB(128, 0, 128)); break; // Lavender
        case 'l': pinkOrangeYellowCycle(100); break;
        case '7': candleEffect(); break;
        case '8': waveEffect(); break;
        case '9': aurora(); break;
        default: break; // Ignore unknown commands
      }
    }
  }

  // Audio playback is handled in the background via a2dp_sink
}

// Helper function to set all LEDs to a specific color
void setColor(CRGB color) {
  fill_solid(leds, NUMPIXELS, color);
  FastLED.show(); // Update the strip to show changes
}

// LED effects
void aurora() {
  for (int i = 0; i < NUMPIXELS; i++) {
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

void candleEffect() {
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate > 50) { // Update every 50ms
    lastUpdate = millis();
    for (int i = 0; i < NUMPIXELS; i++) {
      int brightness = random(120, 255); // Simulate candle brightness
      leds[i] = CHSV(32, 255, brightness); // Candle color (yellowish light)
    }
    FastLED.show();
  }
}

void waveEffect() {
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate > 30) { // Update every 30ms
    lastUpdate = millis();
    for (int i = 0; i < NUMPIXELS; i++) {
      float phase = i * 2 * PI / NUMPIXELS; // Calculate the phase shift
      int brightness = 128 + 127 * sin(millis() / 100.0 + phase);
      brightness = constrain(brightness, 0, 255);
      leds[i] = CRGB(0, brightness / 2, brightness); // Cyan and blue wave
    }
    FastLED.show();
  }
}

void pinkOrangeYellowCycle(int wait) {
  static unsigned long lastUpdate = 0;
  static int currentColor = 0;

  if (millis() - lastUpdate > wait) { // Update based on the wait time
    lastUpdate = millis();
    CRGB colors[] = {CRGB::Pink, CRGB(255, 165, 0), CRGB::Yellow}; // Colors to cycle
    int numColors = sizeof(colors) / sizeof(colors[0]);

    for (int i = 0; i < NUMPIXELS; i++) {
      leds[i] = colors[(i + currentColor) % numColors];
    }
    currentColor = (currentColor + 1) % numColors;
    FastLED.show();
  }
}
