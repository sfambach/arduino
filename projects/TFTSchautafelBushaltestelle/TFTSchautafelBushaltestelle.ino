/**
 * Schautafel mit ESP32 
 */
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Persil1.c"
#include "Persil2.c"
#include "Persil5.c"


// Michaels Display
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

void setup(void) {

  Serial.begin(115200);
  Serial.println("Initialized");
  
  tft.init();
  tft.setSwapBytes(true); // big to little or vice versa
  tft.fillScreen(TFT_WHITE); // hintergrund weiss füllen wie bei Lichtafeln 
  //tft.fillScreen(TFT_BLACK); // Lieber schwarzer Hintergrund?
  tft.initDMA();

}

int delayMS = 10000;

void loop() {

  Serial.println("Persil 1");
  tft.pushImage(0, 0, 93, 116, Persil1); 
  //tft.pushImage(17, 6, 93, 116, Persil1); // ums in die mitte zu bekommen 
  delay(delayMS);

  Serial.println("Persil 2");
  tft.fillScreen(TFT_WHITE);
  tft.pushImage(0, 0, 79, 115, Persil2); 
  delay(delayMS);

  Serial.println("Persil 5");
  tft.fillScreen(TFT_WHITE);
  tft.pushImage(0, 0 , 84, 116, Persil5); 
  delay(delayMS);
}
