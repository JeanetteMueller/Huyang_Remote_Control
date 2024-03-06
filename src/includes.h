#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Arduino_GFX_Library.h>
#include "classes/HuyangFace/HuyangFace.h"
#include "classes/HuyangBody/HuyangBody.h"
#include "classes/HuyangNeck/HuyangNeck.h"