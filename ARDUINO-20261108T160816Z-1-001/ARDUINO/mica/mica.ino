#include <driver/gpio.h>
#include <driver/i2s.h>
#include <FastLED.h>
#include "BluetoothSerial.h"
#include "BluetoothA2DPSink.h"

#define LED_PIN 18
#define NUMPIXELS 30
CRGB leds[NUMPIXELS];

BluetoothSerial SerialBT;
BluetoothA2DPSink a2dp_sink;

#define I2S_DOUT_PIN GPIO_NUM_15
#define I2S_BCLK_PIN GPIO_NUM_23
#define I2S_WS_PIN GPIO_NUM_22

unsigned long previousMillisCandle = 0;
unsigned long previousMillisaurora = 0;
unsigned long previousMillisWave = 0;
const long intervalCandle = 100;
const long intervalWave = 100;
const long intervalaurora = 100;
 static unsigned long previousMillisbreath = 0;
    const long intervalbreath = 20; // Adjust speed of breathing effect

    static uint8_t brightnessbreath = 50; // Starting brightness
    static int directionbreath = 5;       // Controls fade in/out speed

int activeEffect = -1;

void setColor(CRGB color) {
    fill_solid(leds, NUMPIXELS, color);
    FastLED.show();
}

void setup() {
    Serial.begin(115200);
    SerialBT.begin("FOM_Lamp");
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUMPIXELS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(255);
    setColor(CRGB::White);
    FastLED.show();
    Serial.println("ESP32 Ready with LED and Audio!");

    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_BCLK_PIN,
        .ws_io_num = I2S_WS_PIN,
        .data_out_num = I2S_DOUT_PIN,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
    a2dp_sink.set_i2s_port(I2S_NUM_0);
    a2dp_sink.set_pin_config(pin_config);
    a2dp_sink.start("FOM_Speaker");
}

void loop() {
    unsigned long currentMillis = millis();
    
    if (SerialBT.available()) {
        String data = SerialBT.readStringUntil('\n');
        Serial.println("Received: " + data);


        if (data.startsWith("B")) {
            int brightness = data.substring(1).toInt();
            if (brightness >= 0 && brightness <= 255) {
                FastLED.setBrightness(brightness);
                FastLED.show();
            }
        }
        
 if (data.indexOf(",") != -1) {
            int r, g, b;
            sscanf(data.c_str(), "%d,%d,%d", &r, &g, &b);
            setColor(CRGB(r, g, b));
            activeEffect = -1;
            return;
 }

        char command = data[0];
        if (command == '1') { setColor(CRGB::White); activeEffect = -1; }
        else if (command == '0') setColor(CRGB::Black);
        else if (command == 'a') setColor(CRGB::Yellow);
        else if (command == 'b') setColor(CRGB(255, 165, 0));
        else if (command == 'c') setColor(CRGB(255, 18, 22));
        else if (command == 'd') setColor(CRGB::Blue);
        else if (command == 'e') setColor(CRGB::Cyan);
        else if (command == 'f') setColor(CRGB::Navy);
        else if (command == 'g') setColor(CRGB::Green);
        else if (command == 'h') setColor(CRGB(139, 69, 19));
        else if (command == 'i') setColor(CRGB::Purple);
        else if (command == 'j') setColor(CRGB(141, 255, 255));
        else if (command == 'k') setColor(CRGB(128, 0, 128));
        else if (command == '2') activeEffect = 2;
        else if (command == '3') activeEffect = 3;
        else if (command == '4') activeEffect = 4;
        else if (command == '5') activeEffect = 5;
        else if (command == '6') activeEffect = 6;
        else if (command == '7') activeEffect = 7;
    }
    
    if (activeEffect == 3 && currentMillis - previousMillisCandle >= intervalCandle) {
        previousMillisCandle = currentMillis;
        candle();
    }
    else if (activeEffect == 5 && currentMillis - previousMillisWave >= intervalWave) {
        previousMillisWave = currentMillis;
        wave();
    }
    else if (activeEffect == 4 && currentMillis - previousMillisaurora >= intervalaurora) {
        previousMillisaurora = currentMillis;
        aurora();
    }
    else if (activeEffect == 2) setWaveEffect();
    else if (activeEffect == 6) neon();
    else if (activeEffect == 7) breathingEffect();  
}

void setWaveEffect() {
    for (int i = 0; i < NUMPIXELS; i++) {
        float phase = i * 2 * PI / NUMPIXELS;
        int brightness = 128 + 127 * sin(millis() / 100.0 + phase);
        leds[i] = CRGB(0, brightness / 2, brightness);
    }
    FastLED.show();
}

void candle() {
    for (int i = 0; i < NUMPIXELS; i++) {
        int brightness = random(100, 255);
        leds[i] = CRGB(brightness, brightness / 2, 0);
    }
    FastLED.show();
}

void aurora() {
    for (int i = 0; i < NUMPIXELS; i++) {
        int hue = random(0, 255);
        leds[i] = CHSV(hue, 255, 255);
    }
    FastLED.show();
}

void wave() {
    for (int i = 0; i < NUMPIXELS; i++) {
        leds[i] = CRGB(0, random(100, 255), random(0, 255));
    }
    FastLED.show();
}

void neon() {
    static uint8_t hue = 0;
    hue++;
    for (int i = 0; i < NUMPIXELS; i++) {
        leds[i] = CHSV(hue, 255, 255);
    }
    FastLED.show();
}

void breathingEffect() {

    if (millis() - previousMillisbreath >= intervalbreath ) {
        previousMillisbreath = millis();
        brightnessbreath += directionbreath;

        if (brightnessbreath <= 50 || brightnessbreath >= 255) {
            directionbreath = -directionbreath; // Reverse direction at min/max brightness
        }

        FastLED.setBrightness(brightnessbreath);
        FastLED.show();
    }
}


