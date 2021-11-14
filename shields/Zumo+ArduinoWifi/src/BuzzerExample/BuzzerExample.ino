#include <ZumoShield.h>
ZumoBuzzer buzzer;

void setup() {
   buzzer.play(">g32>>c32");
}

void loop() {
   buzzer.play(">g32>>c32");
   delay (1000);
}
