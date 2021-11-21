/******************************************************************
   Car with PS2 remote controle
   Author: S. Fambach
   fambach.net

*/

/******************************************************************
   PS2 Controller settings
*/
#include <PS2X_lib.h>  //for v1.6
#define PS2_DAT        12
#define PS2_CMD        11
#define PS2_SEL        10
#define PS2_CLK        13

#define pressures  true
#define rumble      true

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;


const int MODE_RC = 0; // remote control
const int MODE_FD = 1; // free drive
int currentMode = MODE_RC;

/******************************************************************/


void setup() {

  Serial.begin(115200);

  delay(300);

  // pins des controllers setzen
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  switch (error) {
    case 0:
      Serial.print("Controller gefunden");
      Serial.print("pressures = ");
      if (pressures)
        Serial.println("true");
      else
        Serial.println("false");
      Serial.print("rumble = ");
      if (rumble)
        Serial.println("true)");
      break;

    case 1: Serial.println("Kein Controller gefunden"); break;
    case 2: Serial.println("Controller gefunden, er aktzeptiert aber keine eingehenden Kommandos"); break;
    case 3: Serial.println("Controller unterstützt keine Drucktasten"); break;
  }


  type = ps2x.readType();
  switch (type) {
    case 0: Serial.print("Unbekannter Controller"); break;
    case 1: Serial.print("DualShock Controller"); break;
    case 2: Serial.print("GuitarHero Controller, Das Programm wird nicht richtig funktionieren"); break;
    case 3: Serial.print("Wireless Sony DualShock"); break;
  }
}

void stop() {

  // stoppe motoren

  // stopoe Servos


  // stoppe ?
}


void rcDrive(){}
void freeDrive(){};

void loop() {

  if (error == 1)
    return; // reset einfügen

  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed


  // PSB_START, PSB_SELECT, PSB_PAD_UP, PSB_PAD_RIGHT, PSB_PAD_LEFT, PSB_PAD_DOWN

  // zuerst den Modus überprüfen dann handen.
  if (ps2x.ButtonPressed(PSB_CIRCLE)) {
    Serial.println("Free Drive Modus aktiviert");
    stop();
    currentMode = MODE_FD;
    vibrate = 255;
  }
  if (ps2x.ButtonPressed(PSB_SQUARE))
  {
    Serial.println("RC Modus aktiviert");
    stop();
    currentMode = MODE_RC;
    vibrate = 255;
  }
  if (ps2x.ButtonPressed(PSB_CROSS)) {
    Serial.println("Modus noch nicht supported");
  }
  if (ps2x.ButtonPressed(PSB_TRIANGLE)) {
    Serial.println("Modus noch nicht supported");
  }

  if (ps2x.ButtonReleased(PSB_CIRCLE) ||
      ps2x.ButtonReleased(PSB_SQUARE) ||
      ps2x.ButtonReleased(PSB_CROSS) ||
      ps2x.ButtonReleased(PSB_TRIANGLE) ) {
    vibrate = 0;

  }

  switch (currentMode) {
    case MODE_RC: rcDrive(); break;
    case MODE_FD: freeDrive(); break;
  }

  delay(50);
}
