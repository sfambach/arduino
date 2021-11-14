#pragma once
#include "arduino_secrets.h" 

void printMacAddress(byte mac[]);
void printWifiData() ;
boolean checkWifiConnection();
void printCurrentNet();

int status = WL_IDLE_STATUS;     // the WiFi radio's status
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)


boolean wifiConnected = false;
long loginTimer = 0;
long timeout = 6000;

boolean checkWifiConnection(){


  // check if timout is reached
  if( millis() - loginTimer < timeout){

    if(millis() - loginTimer % 100 == 0){
      Serial.print(".");
    }
    return false;
  }
  
  if (status != WL_CONNECTED) {
    loginTimer = millis();
    wifiConnected = false;
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(SECRET_SSID, SECRET_PASS);
    return false;
    
  } else {
    if(!wifiConnected){
      wifiConnected = true;
      Serial.println("Connected to WiFi");
      printWifiData();    
    }
    return true;
  }
}


void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}

void printWifiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}
