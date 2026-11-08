#include <FastLED.h>
#include "BluetoothSerial.h"
#include "BluetoothA2DPSink.h"
#include <time.h>  // Library for handling time

#define PIN 18
#define NUMPIXELS 10

CRGB leds[NUMPIXELS];

BluetoothSerial SerialBT;
BluetoothA2DPSink a2dp_sink;

// Variables for LED on schedule
int scheduledHourOn = -1;
int scheduledMinuteOn = -1;
bool scheduleOnActive = false;

// Variables for LED off schedule
int scheduledHourOff = -1;
int scheduledMinuteOff = -1;
bool scheduleOffActive = false;

void setup() {
  Serial.begin(115200);

  const char* deviceName = "FOM Speaker";
  SerialBT.begin(deviceName);
  a2dp_sink.start(deviceName);

  FastLED.addLeds<WS2812, PIN, RGB>(leds, NUMPIXELS);
  FastLED.clear();
  FastLED.show();

  // Initialize time (assuming an RTC module or Internet time sync)
  configTime(0, 0, "pool.ntp.org");  // NTP for time sync
  Serial.println("ESP32 Speaker Ready with LED Control!");
}

void loop() {
  // Handle LED control commands via Bluetooth Serial
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');  // Read the full command as a string
    Serial.println(command);

    if (command.startsWith("A")) {
      // Parse the hour and minute for LED on schedule
      scheduledHourOn = command.substring(1, 3).toInt();
      scheduledMinuteOn = command.substring(3, 5).toInt();
      scheduleOnActive = true;
      Serial.printf("LED on schedule set for %02d:%02d\n", scheduledHourOn, scheduledMinuteOn);
    } else if (command.startsWith("C")) {
      // Parse the hour and minute for LED off schedule
      scheduledHourOff = command.substring(1, 3).toInt();
      scheduledMinuteOff = command.substring(3, 5).toInt();
      scheduleOffActive = true;
      Serial.printf("LED off schedule set for %02d:%02d\n", scheduledHourOff, scheduledMinuteOff);
    } else if (command == "B") {
      // Cancel all schedules
      scheduleOnActive = false;
      scheduleOffActive = false;
      scheduledHourOn = -1;
      scheduledMinuteOn = -1;
      scheduledHourOff = -1;
      scheduledMinuteOff = -1;
      Serial.println("All schedules cancelled");
    } else {
      // Handle other LED color commands
      handleLEDCommands(command[0]);
    }
  }

  // Check the current time and activate the schedules if it's time
  time_t now = time(NULL);
  struct tm* currentTime = localtime(&now);
  int currentHour = currentTime->tm_hour;
  int currentMinute = currentTime->tm_min;

  // Trigger LED on schedule
  if (scheduleOnActive && currentHour == scheduledHourOn && currentMinute == scheduledMinuteOn) {
    setColor(CRGB(255, 255, 255));  // Turn on LEDs (white)
    scheduleOnActive = false;  // Deactivate schedule after triggering
    Serial.println("LEDs turned on as scheduled!");
  }

  // Trigger LED off schedule
  if (scheduleOffActive && currentHour == scheduledHourOff && currentMinute == scheduledMinuteOff) {
    setColor(CRGB(0, 0, 0));  // Turn off LEDs
    scheduleOffActive = false;  // Deactivate schedule after triggering
    Serial.println("LEDs turned off as scheduled!");
  }

  delay(1000);  // Small delay to reduce CPU load
}

// Helper function to handle LED commands
void handleLEDCommands(char command) {
  switch (command) {
    case '1': setColor(CRGB(255, 255, 255)); break;  // White
    case '0': setColor(CRGB(0, 0, 0)); break;        // Off
    case 'a': setColor(CRGB(255, 255, 0)); break;    // Yellow
    case 'b': setColor(CRGB(255, 165, 0)); break;    // Orange
    case 'c': setColor(CRGB(255, 192, 203)); break;  // Pink
    case 'd': setColor(CRGB(0, 0, 255)); break;      // Blue
    case 'e': setColor(CRGB(0, 255, 255)); break;    // Cyan
    case 'f': setColor(CRGB(0, 0, 128)); break;      // Navy Blue
    case 'g': setColor(CRGB(0, 255, 0)); break;      // Green
    case 'h': setColor(CRGB(139, 69, 19)); break;    // Brown
    case 'i': setColor(CRGB(128, 0, 128)); break;    // Purple
    case 'j': setColor(CRGB(173, 216, 230)); break;  // Light Blue
    case 'k': setColor(CRGB(230, 230, 250)); break;  // Lavender
    case 'l': pinkOrangeYellowCycle(100); break;     // Alternating colors
    default: break;                                  // Ignore unknown commands
  }
}


// Helper function to set all LEDs to a specific color
void setColor(CRGB color) {
  fill_solid(leds, NUMPIXELS, color);
  FastLED.show();
}

// Helper function for alternating colors
void pinkOrangeYellowCycle(int wait) {
  const CRGB colors[] = {CRGB(255, 255, 0), CRGB(255, 192, 203), CRGB(255, 165, 0)};
  static int offset = 0;

  for (int i = 0; i < NUMPIXELS; i++) {
    leds[i] = colors[(i + offset) % 3];
  }
  FastLED.show();
  delay(wait);
  offset = (offset + 1) % 3;
}
