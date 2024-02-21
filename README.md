# Huyang Remote Control
Software for ESP8266 and ESP32 to control Huyang from DroidDivision via Browser/Mobile Device.
This Software runs on mostly any ESP32 and ESP826 together with two GC9A01 TFT Displays. 
Inside the Folder /Wiring Diagrams you can find some Instructions how to connect two GC9A01 Displays to common Boards. 

# HOW TO Get this running!!!

To get this running, change the WifiSsid to whatever your wifi should be called this Wifi will be created by Huyang himself. Don' name this like your home Wifi.

> #define WifiSsid "HuyangWifiControl" // <- change if needed

set a custom passwort so not everyone can control your Huyang Droid

> #define WifiPassword "<YOUR WIFI PASSWORD>"

The Webserver is per default accessible via 192.168.10.1:80
If you want to change this, change the line of this file with "IPAddress apIP" in the beginning. 
And the Port

> #define ServerPort 80

# Install Board Library
1. Open "Tools" -> "Board ..." -> "Board Manager"
2. Search for "esp"
3. Install "esp32 by Espressif" OR "ESP8266 Boards (x.x.x)" to make your Board available
4. Select "Tools" -> "Board" -> ... whatever you have. Maybe "Generic ESP8266 Module", or "ESP32 Dev Modul"

# Install Software Libraries
1. Open "Tools" -> "Manage Libraries"
2. Search for following Names and install what you found
3. "Arduino GFX Library" -> Install "GFX Library for Arduino by Moon On Our Nation"
4. "ESPAsyncWebServer" -> Install "ESPAsyncWebServer by Iacamera"
5. "AsyncTCP" -> Install "AsyncTCP by dvarrel"


# Changelog

## 1.0 Inital Version
* With Webserver
* Control Eyes Open and Close
* Eyes can Blink

## 1.1 New Gestures 
* Faster Blink
* Sad Mood
* Angry Mood
* Focus Mood

## 1.2 Refactoring
* Bugfixing
* All Face Moods controlled with one HuyangFace Class

## 1.3 Whole Body preparations
* New empty Class: HuyangBody will control Torso rotation, roll, tilt and yaw
* New empty Class: HuyangNeck will control Head/Neck rotation, roll, tilt and yaw

