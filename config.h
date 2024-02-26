// Install Libraries
// Please read the "README.md"


// Huyang Wifi Modes 
// 0 = creates his own wifi with the following Data
// 1 = connects to a existing wifi with the following credentials
#define WiFiMode 0

// To get this running, change the WifiSsid to whatever your wifi should be called
// this Wifi will be created by Huyang himself. Don' name this like your home Wifi.
#define WifiSsid "HuyangWifiControl" // <- change if needed

// set a custom passwort so not everyone can control your Huyang Droid
#define WifiPassword "<YOUR WIFI PASSWORD>"



// ONLY if the Huyang Wifi Mode is 0:
// The Webserver is per default accessible via 192.168.10.1
IPAddress apIP(192, 168, 10, 1);
#define ServerPort 80
// If you change the Port to something different than 80, like 301
// Huyang will be accessible via 192.168.10.1:301

// ONLY if the Huyang Wifi Mode is 1:
// Conenct to your Wifi Router and check the connected Devices to get his IP Adress
// When connected wia USB, the console will write down the current IP Adress 3 times on bootup