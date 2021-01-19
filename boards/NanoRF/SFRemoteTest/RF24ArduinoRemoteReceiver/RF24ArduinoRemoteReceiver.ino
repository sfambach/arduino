// nRF receiver for Sunfounder Remote 
// www.fambach.net
// GPL2
/***********************************************************/
// radio
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define SWITCH 0
#define X 1
#define Y 2


#define PIN_CE  10
#define PIN_CSN 9
RF24 radio(PIN_CE, PIN_CSN);
byte addresses[][6] = {"007", "001"};
int data[3] = {0,512, 512}; 



/***********************************************************/

void setup() {
  Serial.begin(9600);

  Serial.println("init rf");
  radio.begin();                      // initialize RF24
  radio.setRetries(0, 15);            // set retries times
  radio.setPALevel(RF24_PA_LOW);      // set power
  // radio.setChannel(99); // Suggestion from Jens in case of any trouble activate this
  
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
    bool done = false;
    while (radio.available())
    {
      // Fetch the data payload
      radio.read( data, sizeof(data) );
      Serial.print("SWITCH = ");
      Serial.print(data[SWITCH]);
      Serial.print(" X = ");
      Serial.print(data[X]);
      Serial.print(" Y = ");
      Serial.println(data[Y]);
      

    }
  }
  else
  {
    // Serial.println("No radio available"); only for test 
  }

}


