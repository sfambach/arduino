// Nano Remote Receiver
// This programm receives a char array with maximum size 20
// www.fambach.net
//
// Libs:
// https://github.com/tmrh20/RF24/
// 
// GPL2
/***********************************************************/
// radio
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define PIN_CE  10
#define PIN_CSN 9

RF24 radio(PIN_CE, PIN_CSN);
byte addresses[][6] = {"007", "001"};

#define SIZE 20 
char buf[SIZE];

/***********************************************************/

void setup() {

  Serial.begin(9600);
  delay(4000);

Serial.println("SPI settings");
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_2XCLOCK_MASK);

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
    bool done = false;
    while (radio.available())
    {
      // Fetch the data payload
      radio.read( buf, sizeof(buf));

//      for(int i = 0; i < 20; i ++){
//        Serial.print((char)buf[i]);
//      }
      Serial.println(buf);
    }
  }
  else
  {
    // Serial.println("No radio available"); //only for test purpose
  }
}


