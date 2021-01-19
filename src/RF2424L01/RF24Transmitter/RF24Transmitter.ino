// this program transmitts a single integer value
// http://www.fambach.net
/*************************************************/
// RF
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define PIN_CE   9
#define PIN_CSN 10

RF24 radio(PIN_CE, PIN_CSN); // define the object to control NRF24L01
byte addresses[][6] = {"007", "001"};
int data[1] = {0};

void setup() {
  Serial.begin(9600);

  /***********************************************************************/
  // init radio
  radio.begin();                      // initialize RF24
  radio.setRetries(0, 15);            // set retries times
  radio.setPALevel(RF24_PA_LOW);      // set power
  radio.openWritingPipe(addresses[1]);  // open delivery channel
  radio.openReadingPipe(1, addresses[0]);
  radio.stopListening();

}

void loop() {

  for(int i = 0; i < 255; i++){
    Serial.print("Send: ");
    Serial.println(i);
    data[0] = i; // write current integer to the transfer array
    radio.write(data, sizeof(data)); // send array
    delay(1000); // wait a second
  }
 
}
