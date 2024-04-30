//
// Huyang Network Config
//

// Huyang Wifi Modes 
// WifiModeHotspot = creates his own wifi with the following Data
// WifiModeNetwork = connects to a existing wifi with the following credentials
// #define WiFiDefaultMode JxWifiManager::WifiModeHotspot
#define WiFiDefaultMode JxWifiManager::WifiModeNetwork

// To get this running, change the WifiSsid to whatever your wifi should be called
// this Wifi will be created by Huyang himself. Don' name this like your home Wifi.
#define WifiSsidOfHotspot "HuyangWifiControl" // <- change if needed

// set a custom passwort so not everyone can control your Huyang Droid
#define WifiPasswordHotspot "<YOUR HOTSPOT PASSWORD>" // <- change if needed


// Connect to your local Wifi. If not Accessible Huyang will create Hotspot 
#define WifiSsidConnectTo "<YOUR WIFI SSID>" // <- change if needed
#define WifiPasswordConnectTo "<YOUR WIFI PASSWORD>" // <- change if needed
 

// ONLY if the Huyang Wifi Mode is Mode WifiModeNetwork:
// Connect to your Wifi Router and check the connected Devices to get his IP Adress
// When connected via USB, the console will write down the current IP Adress every 5 seconds.

//Webserver Port default is 80. If you want a different Port, change it
#define WebServerPort 80


// System Option
// Here you can enable/disable some sub-sections of the software to match your build

// the two TFT Displays as eyes
bool enableEyes = true;

// the servo inside of the head shell to move the monacle
bool enableMonacle = true; 

// the two servos inside of the head
bool enableNeckMovement = true; 
// the rotation servo on the bottom of the neck
bool enableHeadRotation = true; 
// the four 60kg servos from the c-3po build plan
bool enableBodyMovement = true; 
// the 80kg servo inside of the hip
bool enableBodyRotation = true; 

// the two lights on the left fromt torso
bool enableTorsoLights = true; 