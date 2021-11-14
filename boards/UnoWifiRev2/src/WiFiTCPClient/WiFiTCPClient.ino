/*
  TCP Client

  initial sketch created by dlf 13 July 2010
  modified 31 May 2012 by Tom Igoe
  modified 19 Nov 2021 by Stefan Fambach
*/


#include <SPI.h>
#include <WiFiNINA.h>
#include "wifi_tools.h"
#include "arduino_secrets.h"

int keyIndex = 0;


// TCP/IP Client
WiFiClient client;

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

}


boolean checkServerConnection() {
  
  if (client.connected()) {
    return true;
  } 
  
  Serial.print("Try to connect to server ");
  Serial.print(SERVER);
  Serial.print(" . ");
  Serial.println(PORT);
  if (client.connect(SERVER, PORT)) {
    Serial.println("connected to server");
    return true;
  } else {

    Serial.println("Connection to server failed");
    return false;
  }
}

void loop() {

  if (! checkWifiConnection()) {
    return;
  }

  if (!checkServerConnection()) {
    return;
  }

  // faking a gyroskope telegram
  String s;
  s.reserve(100);
  s += "1;";
  s += random(0, 360);
  s += ";";
  s += random(0, 360);
  s += ";"; 
  s += random(0, 360);
  
  Serial.println(s);
  client.println(s);


  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // I know delays are bad but this is only a test and
  // I do not want a message every millisecond, thats really to much
  delay (2000);

}
