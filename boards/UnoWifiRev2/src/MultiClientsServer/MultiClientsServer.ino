#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h"

/*******************************************************************************************/
/** activate able debugging output */
#define DEBUG;

#ifdef DEBUG

#define DPRINT(x) Serial.print(x)
#define DPRINTLN(x) Serial.println(x)

#else

#define DPRINT(x)
#define DPRINTLN(x)

#endif;


/*******************************************************************************************/
/** Wifi Settings
*/
#include "wifi_tools.h"



/*******************************************************************************************/
/** server settings

*/
WiFiServer server(SERVER_PORT);
WiFiClient clients[MAX_CLIENTS];
String message;


/*******************************************************************************************/

void setup() {
  //Initialize serial and wait for port to open:
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

  // attempt to connect to WiFi network:
  checkWifiConnection();

  // you're connected now, so print out the data:
  DPRINTLN("You're connected to the network");
  printCurrentNet();
  printWifiData();

  server.begin();


}


void printSlotInfo(int slot, String info , String additionalInfo) {
  DPRINT("Slot ");
  DPRINT(slot);
  DPRINT(" : ");
  DPRINT(info);
  DPRINT(" ... ");
  DPRINT(additionalInfo);
  DPRINT("\n");
}


void loop() {

  checkWifiConnection();

  // check http client connection

  // listen for incoming clients
  WiFiClient client = server.available();

  // put new client in the list
  if (client) {
    //DPRINTLN("new client");

    // check if client is already in the list
    boolean clientAlreadyInList = false;
    for (int i = 0; i < MAX_CLIENTS; i++) {

      if (!clients[i]) {
        continue;
      }

      if (clients[i] == client && clients[i].remoteIP() == client.remoteIP() &&  clients[i].remotePort() == client.remotePort()) {

        String s = "";
        s.reserve(30);
        s += client.remoteIP()[0];
        s += ".";
        s += client.remoteIP()[1];
        s += ".";
        s += client.remoteIP()[2];
        s += ".";
        s += client.remoteIP()[3];
        s += " : ";
        s += client.remotePort();
        printSlotInfo(i, "Client Already in the list, only one client per ip port allowed - using new one", s) ;
        clientAlreadyInList = true;
        //clinets[i].close();
        clients[i] = client;
      }
    }

    if (!clientAlreadyInList) {
      // add new client to list
      for (int i = 0; i < MAX_CLIENTS; i++) {

        if (!clients[i]) {
          printSlotInfo(i, "New Client", "Slot was empty") ;
          clients[i] = client;
          break;
        }

        if (!clients[i].connected() && !clients[i].available()) {
          printSlotInfo(i, "Client not connected so close the socket", "") ;
          clients[i].stop();
          clients[i] = client;
          break;
        }
      }
    }
  } else {
    // DPRINTLN("Wait for clients");
  }

  // receive data
  for (int i = 0; i < MAX_CLIENTS; i++) {

    // client empty go to next
    if (!clients[i]) {
      continue;
    }

    // client not connected go to next
    if ( !clients[i].connected() && !clients[i].available()) {

      continue;
    }

    // so client is connected lets get some data

    message = "";
    message.reserve(200);
    while (clients[i].available() > 0) {
      char c = clients[i].read();
      message += c;
    }
    if (message.length() > 0 ) {
      printSlotInfo(i, "receive data", message) ;
    }


  }


  delay(100);
}
