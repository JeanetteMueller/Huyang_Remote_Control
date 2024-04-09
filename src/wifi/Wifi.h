#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

bool isConnected = false;

void setupWifi()
{
    if (WiFiMode == 0)
    {
        WiFi.mode(WIFI_AP);
        WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
        WiFi.softAP(WifiSsid, WifiPassword, 1, false);
    }
    else
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(WifiSsid, WifiPassword);
    }
}

void loopWifi()
{
    if (WiFiMode == 0)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            if (!isConnected)
            {
                isConnected = true;
                Serial.println(WiFi.localIP());
            }
        }
    }
    else
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            // Serial.println(WiFi.localIP());
        }
        else
        {
            int intRetry = 0;
            Serial.print("Connecting to WiFi ..");
            while (WiFi.status() != WL_CONNECTED && (intRetry < 50))
            {
                Serial.print('.');
                intRetry++;
                delay(500);
            }

            if (WiFi.status() == WL_CONNECTED)
            {
                Serial.println(WiFi.localIP());
            }
        }
    }
}