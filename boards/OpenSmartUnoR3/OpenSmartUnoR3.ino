/** OpenSmart Uno example how to call the test class.
 *  Open Smart uno board is a uno compatible board with discrete parts and 
 *  3 additional leds as well 3 switches and a buzzer.
 *  
 *  www.fambach.net
 *  GPLv2
 */

#include "OpenSmartUnoR3.h"

void setup() {
  Board.init(true);
}

void loop() {
  Board.loop();

}
