#include <Adafruit_NeoPixel.h>
#include "BluetoothSerial.h" // Bluetooth Serial library for LED commands
#include "BluetoothA2DPSink.h" // Bluetooth audio sink library for music playback

#define PIN 18           // Pin connected to the NeoPixel strip
#define NUMPIXELS 30    // Number of pixels in the strip

// Create a NeoPixel object
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

BluetoothSerial SerialBT; // Bluetooth Serial object for LED control
BluetoothA2DPSink a2dp_sink; // Bluetooth audio sink object for music playback

void setup() {
  // Initialize serial communications
  Serial.begin(115200);

  // Set the Bluetooth name as "ESP32 Speaker"
  const char* deviceName = "FOM Speaker";

  // Initialize Bluetooth Serial for LED commands
  SerialBT.begin(deviceName); // Unified name for LED control

  // Initialize the NeoPixel strip
  strip.begin();
  setColor(strip.Color(255, 255, 255)); // Default color to white
  strip.show(); // Turn off all LEDs initially

  // Configure I2S pins for audio output
  i2s_pin_config_t myPins = {
      .bck_io_num = 26,    // BCLK pin (G26)
      .ws_io_num = 25,     // LRC pin (G25)
      .data_out_num = 22,  // DIN pin (G22)
      .data_in_num = I2S_PIN_NO_CHANGE  // No data input
  };

  // Initialize Bluetooth audio sink with I2S configuration
  a2dp_sink.set_pin_config(myPins);  // Apply the I2S pin configuration
  a2dp_sink.start(deviceName);       // Unified name for audio streaming

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
      setColor(strip.Color(r, g, b));
    } else {
      // Handle single-character commands as before
      char command = data[0];

      if (command == '1') {
        setColor(strip.Color(255, 255, 255)); // White
      } else if (command == '0') {
        setColor(strip.Color(0, 0, 0)); // Off
      } else if (command == 'a') {
        setColor(strip.Color(255, 255, 0)); // Yellow
      } else if (command == 'b') {
        setColor(strip.Color(255, 165, 0)); // Orange
      } else if (command == 'c') {
        setColor(strip.Color(255, 0, 255)); // Pink
      } else if (command == 'd') {
        setColor(strip.Color(0, 0, 255)); // Blue
      } else if (command == 'e') {
        setColor(strip.Color(0, 255, 255)); // Cyan
      } else if (command == 'f') {
        setColor(strip.Color(0, 0, 128)); // Navy blue
      } else if (command == 'g') {
        setColor(strip.Color(0, 255, 0)); // Green
      } else if (command == 'h') {
        setColor(strip.Color(139, 69, 19)); // Brown
      } else if (command == 'i') {
        setColor(strip.Color(128, 0, 128)); // Purple
      } else if (command == 'j') {
        setColor(strip.Color(141, 255, 255)); // Light blue
      } else if (command == 'k') {
        setColor(strip.Color(128, 0, 128)); // Lavender
      } else if (command == 'l') {
        pinkOrangeYellowCycle(100); // Alternating colors: Yellow, Pink, Orange
      } else {
        // Ignore unknown commands
      }
    }
  }

  // No need to add code for audio; it runs in the background via a2dp_sink
}

// Helper function to set all LEDs to a specific color
void setColor(uint32_t color) {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show(); // Update the strip to show changes
}

// Helper function for alternating colors
void pinkOrangeYellowCycle(int wait) {
  uint32_t colors[] = {
      strip.Color(255, 192, 203), // Pink
      strip.Color(255, 165, 0),   // Orange
      strip.Color(255, 255, 0)    // Yellow
  };
  int numColors = sizeof(colors) / sizeof(colors[0]);

  for (int i = 0; i < NUMPIXELS; i++) {
    uint32_t color = colors[i % numColors];
    strip.setPixelColor(i, color);
  }

  strip.show();
  delay(wait);
  
}
