#include <WiFi.h>


const int speakerPin = 26;
const int frequency = 440; // 440 Hz


void setup() {
  ledcSetup(0, frequency, 8);
  ledcAttachPin(speakerPin, 0);
  pinMode(speakerPin, OUTPUT);

}

void loop() {
  ledcWrite(0, 128); // 50% duty cycle
  delay(1000);
  ledcWrite(0, 0);
  delay(1000);
}