/*******************************************************************
    The sketch uses the Blynk library to control the colors.

    MakeITModena
 *******************************************************************/
#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <FastLED.h>

// --- FastLed ---
#define NUM_LEDS 16  // remeber, use an external power (battery) if u want to use leds>10
#define DATA_PIN D2  // D2
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 128  // 0-255

bool power = 0;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxx";

// Your WiFi credentials.
char ssid[] = "makeitmodena";
char pass[] = "password";

// Add a on-off BUTTON Widget and set it to SWITH mode. Choose Virtual Pin V0
BLYNK_WRITE(V0) {
    power = param.asInt();
    if (power == 0) {
        Serial.println("Power OFF");
        for (int i = 0; i < NUM_LEDS; i++)
            leds[i].setRGB(0, 0, 0);
        FastLED.show();
    } else
        Serial.println("Power ON");
}

// Add a BUTTON Widget and set it to SWITH mode. Choose Virtual Pin V2
BLYNK_WRITE(V2) {
    bool button = param.asInt();
    Serial.println("colors");

    // turn off all leds
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();

    if (button == 1 && power == 1) {
        for (int flash = 0; flash < 100; flash++) {
            FastLED.setBrightness(flash);
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i] = CRGB::Red;
            }
            FastLED.show();
        }

        for (int flash = 100; flash > 0; flash--) {
            FastLED.setBrightness(flash);
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i] = CRGB::Red;
            }
            FastLED.show();
        }
    }

    // turn off all leds
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
}

// Add a zeRGBa Widget and set it to MERGE mode. Choose Virtual Pin V1
BLYNK_WRITE(V1) {
    // turn off all leds
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();

    FastLED.setBrightness(BRIGHTNESS);
    if (power == 1) {
        int G = param[0].asInt();
        int R = param[1].asInt();
        int B = param[2].asInt();

        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].setRGB(R / 4, G / 4, B / 4);
            FastLED.show();
            delay(100);
        }
        // Do something with x and y
        // Serial.print("R = ");
        // Serial.print(R);
        // Serial.print("; G = ");
        // Serial.print(G);
        // Serial.print("; B = ");
        // Serial.print(B);
        // Serial.println();
    }
}

// --- SETUP ---
void setup() {
    Serial.begin(9600);
    FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    Blynk.begin(auth, ssid, pass);
}

// --- LOOP ---
void loop() {
    Blynk.run();
}