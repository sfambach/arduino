// this example receive a single integer value
// http://www.fambach.net
/***********************************************************/
// radio
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define PIN_CE   9
#define PIN_CSN 10
RF24 radio(PIN_CE, PIN_CSN);
byte addresses[][6] = {"007", "001"};
int data[1] = {0}; 

/***********************************************************/

void setup() {
  Serial.begin(9600);

  Serial.println("init rf");
  radio.begin();                      // initialize RF24
  radio.setRetries(0, 15);            // set retries times
  radio.setPALevel(RF24_PA_LOW);      // set power
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();             // start monitoring

}


void loop()
{
  // receive data ;)
  receiveData();
}



void receiveData() {
  if ( radio.available()) {            // if receive the data

    // Read the data payload until we've received everything
    while (radio.available())
    {
      // Fetch the data payload
      radio.read( data, sizeof(data) );
      Serial.print("Received  = ");
      Serial.println(data[0]);
    }
  }
  else
  {
    // Serial.println("No radio available"); // just for testing that something happens
  }
}


