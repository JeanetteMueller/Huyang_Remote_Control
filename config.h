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
#define WifiPasswordHotspot "<YOUR HOTSPOT PASSWORD>"


// Connect to your local Wifi. If not Accessible Huyang will create Hotspot 
#define WifiSsidConnectTo "Yavin4"
#define WifiPasswordConnectTo "<YOUR WIFI PASSWORD>"
 

// ONLY if the Huyang Wifi Mode is Mode WifiModeNetwork:
// Connect to your Wifi Router and check the connected Devices to get his IP Adress
// When connected via USB, the console will write down the current IP Adress every 5 seconds.

//Webserver Port default is 80. If you want a different Port, change it
#define WebServerPort 80