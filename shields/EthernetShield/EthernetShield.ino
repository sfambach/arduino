#include <SPI.h>

/*******************************************/
// Ethernet
#include <Ethernet.h>
#include "ICMPPing.h"
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};
EthernetClient client;
SOCKET pingSocket = 0;
#define PING_REQUEST_TIMEOUT_MS     2500
ICMPPing ping(pingSocket, (uint16_t)random(0, 255));


/*******************************************/
//Web server things
EthernetServer server(80);


/*******************************************/
//IP dns things
//IPAddress searchIP(192, 168, 1, 0);


/*******************************************/
// own things
int addresses[255];
IPAddress searchIP(192, 168, 1, 0);

void resetAddresses() {
  for (int i = 0; i < 255; i++) {
    addresses[i] = -1;
  }
}

ICMPEchoReply echoResult;
boolean pingStarted = false;

void scanForIp() {

  if (! ping.asyncComplete(echoResult)&& pingStarted) {
    Serial.print(".");
    return;
  }

  pingStarted = true;

  

  if (echoResult.status == SUCCESS)
  {
    Serial.print(echoResult.data.id);
    Serial.print("|");
    Serial.print(echoResult.data.time);
    Serial.print("|");
    for(int i =0; i < REQ_DATASIZE; i++){
      Serial.print((char)echoResult.data.payload[i]);
    }

    
    addresses[searchIP[3]-1] = echoResult.data.time;
    Serial.println("OK");
  } else {
    addresses[searchIP[3]-1] = -1;
    Serial.println("");
  }


  searchIP[3]++;
  Serial.print("Ping ");
  Serial.print(searchIP);
  if (! ping.asyncStart(searchIP, 1, echoResult))
  {
    addresses[searchIP[3]-1]= -1;
    return;
  } 
  
  if (searchIP[3] > 255) {
    searchIP[3] = 1;
  }

}


void setup() {
  /*************************************/
  // serial setup
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port
  }

  /*************************************/
  // ethernet
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }

  /*************************************/
  // server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  /************************************/
  // ping
  ICMPPing::setTimeout(PING_REQUEST_TIMEOUT_MS);

  resetAddresses();

}

void printPage(EthernetClient & requestor) ;
void loop() {

  EthernetClient requestor =  server.available();
  boolean currentLineIsBlank = true;
  while (requestor.connected()) {

    if (requestor.available()) {
      char c = requestor.read();
      Serial.write(c);

      if (c == '\n') {
        if (currentLineIsBlank) {      // last line of http is blank
          Serial.println("print page");
          printPage(requestor);
          currentLineIsBlank = true;
          delay(2);
          // close the connection:
          requestor.stop();
          break;
        } else {
          // you're starting a new line
          currentLineIsBlank = true;
        }
      }
      if ( c != '\r' && c != '\n') {
        currentLineIsBlank = false;
      }

    }
  }
  scanForIp();
}
void printPage(EthernetClient & requestor) {
  // send a standard http response header
  requestor.println(F("HTTP/1.1 200 OK"));
  requestor.println(F("Content-Type: text/html"));
  requestor.println(F("Connection: close"));  // the connection will be closed after completion of the response
  requestor.println(F("Refresh: 60"));  // refresh the page automatically every 5 sec
  requestor.println();
  requestor.println(F("<!DOCTYPE HTML>"));
  requestor.println(F("<html><body  bgcolor='black' text='white'><H1>Reachable IP's</H1><table border='1' borderColor='white' width='300px'>"));

  requestor.println(F("<tr><th>IP Address</th><th>Ping Time</th><th>Status</th></tr>"));
  // output the value of each analog input pin
  IPAddress ip(192, 168, 1, 0);
  for (int i = 0; i < 255; i++) {
    if (addresses[i] > -1) {
    ip[3] = i + 1;
   
    requestor.print(F("<tr><td>"));
    requestor.print(ip);
   // Serial.println(ip);
    requestor.print(F("</td><td>"));
    requestor.print(addresses[i]);
    requestor.print(F("</td><td>ONLINE</td></tr>"));
    }
  }
  requestor.println(F("</table></body></html>"));
}





