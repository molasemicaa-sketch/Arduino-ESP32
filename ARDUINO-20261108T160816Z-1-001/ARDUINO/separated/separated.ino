#include <FastLED.h>
#include "BluetoothSerial.h" // Bluetooth Serial library for LED commands
#include "BluetoothA2DPSink.h" // Bluetooth audio sink library for music playback

#define PIN 18
#define NUMPIXELS 60 // Change this to the number of pixels in your strip

// Define the LED array
CRGB leds[NUMPIXELS];

BluetoothSerial SerialBT; // Bluetooth Serial object for LED control
BluetoothA2DPSink a2dp_sink; // Bluetooth A2DP Sink object for audio playback

void setup() {
  // Initialize serial communications
  Serial.begin(115200);

  // Initialize Bluetooth Serial for LED commands
  SerialBT.begin("ESP32_SmartLamp"); // Set the Bluetooth name of the device

  // Initialize the FastLED library
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUMPIXELS);
  FastLED.clear(); // Turn off all LEDs initially
  FastLED.show();

  // Initialize Bluetooth audio sink
  a2dp_sink.start("ESP32 Speaker"); // Set the Bluetooth name for audio streaming

  Serial.println("ESP32 Smart Lamp Ready with Audio Support!");
}

void loop() {
  // Handle LED control commands via Bluetooth Serial
  if (SerialBT.available()) {
    char command = SerialBT.read(); // Read the incoming command from Bluetooth
    Serial.println(command); // Print the command for debugging

    // Set LED colors based on command
    switch (command) {
      case '1': setColor(CRGB(255, 255, 255)); break; // White
      case '0': setColor(CRGB(0, 0, 0)); break;       // Off
      case 'y': setColor(CRGB(255, 255, 0)); break;   // Yellow
      case 'o': setColor(CRGB(255, 165, 0)); break;   // Orange
      case 'p': setColor(CRGB(255, 192, 203)); break; // Pink
      case 'b': setColor(CRGB(0, 0, 255)); break;     // Blue
      case 'c': setColor(CRGB(0, 255, 255)); break;   // Cyan
      case 'n': setColor(CRGB(0, 0, 128)); break;     // Navy blue
      case 'g': setColor(CRGB(0, 255, 0)); break;     // Green
      case 'v': setColor(CRGB(128, 0, 128)); break;   // Purple
      case 's': setColor(CRGB(139, 69, 19)); break;   // Brown
      case 'l': setColor(CRGB(173, 216, 230)); break; // Light blue
      case 'a': setColor(CRGB(230, 230, 250)); break; // Lavender
      case 'm': setAlternatingColors(); break;        // Alternating colors: Yellow, Pink, Orange
      default: break; // Ignore unknown commands
    }
  }

  // No need to add code for audio; it runs in the background via a2dp_sink
}

// Helper function to set all LEDs to a specific color
void setColor(CRGB color) {
  fill_solid(leds, NUMPIXELS, color);
  FastLED.show(); // Update the strip to show changes
}

// Helper function for alternating colors
void setAlternatingColors() {
  for (int i = 0; i < NUMPIXELS; i++) {
    if (i % 3 == 0) {
      leds[i] = CRGB(255, 255, 0); // Yellow
    } else if (i % 3 == 1) {
      leds[i] = CRGB(255, 192, 203); // Pink
    } else if (i % 3 == 2) {
      leds[i] = CRGB(255, 165, 0); // Orange
    }
  }
  FastLED.show(); // Update the strip to show changes
}
