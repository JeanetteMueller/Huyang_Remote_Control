#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif


bool isConnected = false;

void setupWifi(){

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(WifiSsid, WifiPassword, 1, false);

}

void loopWifi() {

  if (WiFi.status() == WL_CONNECTED) {

    if (!isConnected) {
      isConnected == true;
      Serial.println(WiFi.localIP());
    }
  }
}