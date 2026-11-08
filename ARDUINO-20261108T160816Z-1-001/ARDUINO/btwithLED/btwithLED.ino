#include <Adafruit_NeoPixel.h>
#include "BluetoothSerial.h" // Include the Bluetooth Serial library for ESP32

#define PIN 18
#define NUMPIXELS 60 // Change this to the number of pixels in your strip

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
BluetoothSerial SerialBT; // Create a Bluetooth Serial object

void setup() {
  Serial.begin(9600); // Opc:\Users\tolon\Documents\Arduino\schedulertional, for debugging over USB Serial
  SerialBT.begin("ESP32_SmartLamp"); // Set the Bluetooth name of the device
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.println("Bluetooth Device is Ready to Pair");
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read(); // Read the incoming command from Bluetooth
    Serial.println(command); // Print the command for debugging

    if (command == '1') {
      // Turn on the LEDs (white)
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
      }
      SerialBT.println("on");
    } else if (command == '0') {
      // Turn off the LEDs
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
    } else if (command == 'y') {
      // Turn yellow
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 0));
      }
    } else if (command == 'o') {
      // Turn orange
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(255, 165, 0));
      }
    } else if (command == 'p') {
      // Turn pink
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(255, 192, 203));
      }
    } else if (command == 'b') {
      // Turn blue
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 255));
      }
    } else if (command == 'c') {
      // Turn cyan
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(0, 255, 255));
      }
    } else if (command == 'n') {
      // Turn navy blue
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 128));
      }
    } else if (command == 'g') {
      // Turn green
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(0, 255, 0));
      }
    } else if (command == 'v') {
      // Turn purple
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(128, 0, 128));
      }
    } else if (command == 's') {
      // Turn brown
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(139, 69, 19));
      }
    } else if (command == 'l') {
      // Turn light blue
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(173, 216, 230));
      }
    } else if (command == 'a') {
      // Turn lavender
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(230, 230, 250));
      }
    }

    strip.show(); // Update the strip to show changes
  }
}
