#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
//#include <ESP8266WiFiMulti.h>
#include <DNSServer.h>            //WifiMan
#include <ESP8266WebServer.h>     //WifiMan
#include <WiFiManager.h>          //WifiMan

// ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

const char* ssid1 = "r6wifi" ;
const char* password1 = "internet" ;
const char* ssid2 = "Rb706" ;
const char* password2 = "724L@zneB" ;
const char* ssid3 = "Radka-Guest" ;
const char* password3 = "R@dk@2108" ;
String aHostname = "SmartRelay";
WiFiManager wifiManager;                      //WifiMan

void setup_Wifi() {
  WiFi.hostname(aHostname);
  delay(100);
  /*
  wifiMulti.addAP(ssid1, password1);   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP(ssid2, password2);
  wifiMulti.addAP(ssid3, password3);
  Serial.println("Connecting ...");
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(50);
    Serial.print('.');
  }
  */
  
  wifiManager.autoConnect("TimeRelayAP");     //WifiMan
  //wifiManager.resetSettings();
  //Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
   if (MDNS.begin(aHostname)) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }
}

void wifiReset() {
  wifiManager.resetSettings();
  WiFi.mode(WIFI_STA);
  
  WiFi.persistent(true);
  WiFi.disconnect(true);
  WiFi.persistent(false);
  delay(2000);
  //wifiManager.startConfigPortal("OnDemandAP");
  ESP.reset();
}
