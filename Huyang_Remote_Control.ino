// HOW TO Get this running!!!
//
// To get this running, change the WifiSsid to whatever your wifi should be called
// this Wifi will be created by Huyang himself. Don' name this like your home Wifi.
#define WifiSsid "HuyangWifiControl" // <- change if needed
// set a custom passwort so not everyone can control your Huyang Droid
#define WifiPassword "<YOUR WIFI PASSWORD>"
// The Webserver is per default accessible via 192.168.10.1:301
// If you want to change this, change the line of this file with "IPAddress apIP" in the beginning.
// and the Port
#define ServerPort 80


// Install Board Library
// Open "Tools" -> "Board ..." -> "Board Manager"
// Search for "esp"
// Install "esp32 by Espressif" OR "ESP8266 Boards (x.x.x)" to make your Board available
// Select "Tools" -> "Board" -> ... whatever you have. Maybe "NodeMCU 0.3 (ESP-12 Modul)", or "ESP32 Dev Modul"
//
// Install Software Libraries
// Open "Tools" -> "Manage Libraries"
// Search for following Names and install what you found
// "Arduino GFX Library" -> Install "GFX Library for Arduino by Moon On Our Nation"
// "ESPAsyncWebServer" -> Install "ESPAsyncWebServer by Iacamera"
// "AsyncTCP" -> Install "AsyncTCP by dvarrel"
// "Adafruit PWM Servo Driver" -> Install "Adafruit PWM Servo Driver Library" by Adafruit


#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

// define your webservice IP Adress
IPAddress apIP(192, 168, 10, 1);

#include <Arduino_GFX_Library.h>
#include <Adafruit_PWMServoDriver.h>
#include "src/classes/HuyangFace/HuyangFace.h"
#include "src/classes/HuyangBody/HuyangBody.h"
#include "src/classes/HuyangNeck/HuyangNeck.h"

Arduino_DataBus *leftBus = new Arduino_HWSPI(0 /* DC */, 15 /* CS */);
Arduino_GFX *leftEye = new Arduino_GC9A01(leftBus, 0 /* RST */);

Arduino_DataBus *rightBus = new Arduino_HWSPI(0 /* DC */, 16 /* CS */);
Arduino_GFX *rightEye = new Arduino_GC9A01(rightBus, 0 /* RST */);

Adafruit_PWMServoDriver pwm_body = Adafruit_PWMServoDriver(0x40);

HuyangFace *huyangFace = new HuyangFace(leftEye, rightEye);
HuyangBody *huyangBody = new HuyangBody(pwm_body); 
HuyangNeck *huyangNeck = new HuyangNeck(pwm_body);

#include "src/wifi/Wifi.h"
#include "src/webserver/WebServer.h"

void setup() {
  Serial.begin(115200);  //Used only for debugging on arduino serial monitor
  Serial.println(F("Huyang! v1.3"));

  setupWifi();

  setupWebserver();

  huyangFace->setup();
  huyangBody->setup();
  huyangNeck->setup();

  Serial.println(F("setup done"));
}

void loop() {
  loopWifi();

  huyangFace->loop();
  huyangBody->loop();
  huyangNeck->loop();
}
