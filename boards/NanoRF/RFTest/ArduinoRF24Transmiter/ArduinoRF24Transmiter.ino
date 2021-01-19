// Nano Remote Transmiter
// This programm sends Hello World! x (x is an index from 0 to 9) 
// www.fambach.net
//
// Libs:
// https://github.com/tmrh20/RF24/
// 
// GPL2
/***********************************************************/
// RF
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define PIN_CE  10
#define PIN_CSN 9

RF24 radio(PIN_CE, PIN_CSN); // define the object to control NRF24L01
byte addresses[][6] = {"007", "001"};
int mode = 1;
#define SIZE 20
char buf[SIZE];

void setup() {
  Serial.begin(9600);

  /***********************************************************************/
  // init radio
  radio.begin();                      // initialize RF24
  radio.setRetries(0, 15);            // set retries times
  radio.setPALevel(RF24_PA_LOW);      // set power
  // radio.setChannel(99); // Suggestion from Jens in case of any trouble activate this
  radio.openWritingPipe(addresses[1]);  // open delivery channel
  radio.openReadingPipe(1, addresses[0]);
  radio.stopListening();

}
int i = 0;
void loop() {

  String s;
  s.reserve(20);
  s = "Hello World! ";
  s += i;
  s.toCharArray(buf, SIZE);
  Serial.println(s);

  radio.write(buf,sizeof(buf));

  i++;
  if (i > 9) i = 0;
  
  delay(1000);
}
