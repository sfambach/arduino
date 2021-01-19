/** 
 *  RF24L01+ example 
 *  this example receive a single integer value
 *  
 *  on Uno connect to spi
 *  ce    - pin 9 but free selectable
 *  csn   - pin 10 but free selectable
 *  MOSI  - Pin 11
 *  MISO  - PIN 12
 *  SCK   - PIN 13
 *  
 * Created by SteFam @ http://www.fambach.net
 *
 * GPLv3 
 * Blah blah blah, free to use. 
 * I invested some time and money in those examples if you want to delete this header 
 * please do not forget to mention at least my website, thanks!  
*/
/***********************************************************/
// radio
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define PIN_CE   9
#define PIN_CSN 10
RF24 radio(PIN_CE, PIN_CSN);
byte addresses[][6] = {"007", "001"};

#define SIZE 5 
int data[SIZE]; 

/***********************************************************/

void setup() {
  Serial.begin(9600);
delay (2000);
  Serial.println("init rf");
  radio.begin();                      // initialize RF24
  radio.setRetries(0, 15);            // set retries times
  radio.setPALevel(RF24_PA_HIGH);      // set power
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
