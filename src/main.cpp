 /*******************************************************************
    The sketch uses the Blynk library to control the colors.

    DaveCalaway & MakeITModena
 *******************************************************************/
#include <Arduino.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <FastLED.h>

// ----------- FastLed ---------------
#define BLYNK_PRINT Serial  // Comment this out to disable prints and save space
#define NUM_LEDS 5          // remeber, use an external power if u want to use leds>10
#define DATA_PIN 5          // D5
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 128  // 0-255
// -----------------------------------
// if you want to use integer nuumber:  R*256*256 + G*256 + B = int
int colors[NUM_LEDS * 3] = {249, 10, 10, 255, 102, 0, 250, 242, 14, 13, 255, 21, 13, 94, 255};  // only 2^8 colors
bool power = 0;
// ---------------------

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "abc";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxx";
char pass[] = "yyy";

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
    int j = 0;
    if (button == 1 && power == 1) {
        Serial.println("colors");
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].setRGB(colors[j], colors[j + 1], colors[j + 2]);
            j = j + 3;
        }
        FastLED.show();
    }
}

// Add a zeRGBa Widget and set it to MERGE mode. Choose Virtual Pin V1
BLYNK_WRITE(V1) {
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

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    Blynk.begin(auth, ssid, pass);
}

void loop() {
    Blynk.run();
}