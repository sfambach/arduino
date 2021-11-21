/* PS2 Controller test
*  adapted by www.fambach.net
*  Uses Lib of
*  Bill Porter
*  www.billporter.info
*  GPL
*  <http://www.gnu.org/licenses/>
********************************************/

#include "PS2X_lib.h"

#define PS2_DAT        12
#define PS2_CMD        11
#define PS2_SEL        10
#define PS2_CLK        13

unsigned int button[] = {PSB_SELECT,
                         PSB_L3,
                         PSB_R3,
                         PSB_START,
                         PSB_PAD_UP,
                         PSB_PAD_RIGHT,
                         PSB_PAD_DOWN,
                         PSB_PAD_LEFT,
                         PSB_L2,
                         PSB_R2,
                         PSB_L1,
                         PSB_R1,
                         PSB_TRIANGLE,
                         PSB_CIRCLE,
                         PSB_CROSS,
                         PSB_SQUARE
                        };

String sbutton[] = {"PSB_SELECT",
                    "PSB_L3",
                    "PSB_R3",
                    "PSB_START",
                    "PSB_PAD_UP",
                    "PSB_PAD_RIGHT",
                    "PSB_PAD_DOWN",
                    "PSB_PAD_LEFT",
                    "PSB_L2",
                    "PSB_R2",
                    "PSB_L1",
                    "PSB_R1",
                    "PSB_TRIANGLE",
                    "PSB_CIRCLE",
                    "PSB_CROSS",
                    "PSB_SQUARE"
                   }   ;
const int BUTTON_COUNT = 16;

bool button_pressed[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

/******************************************************************
   select modes of PS2 controller:
     - pressures = analog reading of push-butttons
     - rumble    = motor rumbling
   uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
#define pressures  false
//#define rumble      true
#define rumble      true

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.
int error = 0;
byte type = 0;
byte vibrate = 0;
// init controller

bool controllerFound = false;
boolean initController() {

  if (controllerFound) {
    return true;
  }

  // so not configured now try to init
  // setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");

    type = ps2x.readType();
    switch (type) {
      case 0:
        Serial.print("Unknown Controller type found ");
        break;
      case 1:
        Serial.print("DualShock Controller found ");
        break;
      case 2:
        Serial.print("GuitarHero Controller found ");
        break;
      case 3:
        Serial.print("Wireless Sony DualShock Controller found ");
        break;
    }
    controllerFound = true;
    return true;
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  return false;
}




void setup() {

  Serial.begin(9600);
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it

  if (MCUSR & (1 << WDRF)) {
    Serial.println("a watchdog reset occurred");
    delay(5000);
  }
  if (MCUSR & (1 << BORF)) {
    Serial.println("a brownout reset occurred");
    delay(5000);
  }
  if (MCUSR & (1 << EXTRF)) {
    Serial.println(" an external reset occurred");
    delay(5000);
  }
  if (MCUSR & (1 << PORF)) {
    Serial.println(" a power on reset occurred");
    delay(5000);
  }
  // Serial.println(" ?????");
  // delay(2000);
}

int ly = 0;
int lx = 0;
int ry = 0;
int rx = 0;

bool firstReading = true;

void loop() {

  //skip loop as long as no controller found
  if (!initController()) { 
    delay(2000);
    Serial.println("ohoho");
    return;
  }

  // get the type of controller
  type = ps2x.readType(); 

  // check if type is supported
  if(type != 1){
    Serial.print("Wrong type : ");
    Serial.println(type);
    return;
  }

  // read gampad buttons
  ps2x.read_gamepad(false, vibrate); 

  // skip the first reading, its non-sense
  if(firstReading){
    firstReading = false;
    return;    
  }

  for (int i = 0; i < BUTTON_COUNT; i++) {
    bool state = ps2x.Button(button[i]);
    if (state != button_pressed[i]) {
      button_pressed[i] = state;
      Serial.print(sbutton[i]);
      Serial.print(" State chanched = ");
      Serial.println(state);
    }
  }


  // check the analog things
  int lyd = ps2x.Analog(PSS_LY);
  if (lyd != ly) {
    ly = lyd;
    Serial.print("Left y ");
    Serial.println(ly);
  }

  int lxd = ps2x.Analog(PSS_LX);
  if (lxd != lx) {
    lx = lxd;
    Serial.print("Left x ");
    Serial.println(lx);
  }

  int rxd = ps2x.Analog(PSS_RX);
  if (rxd != rx) {
    rx = rxd;
    Serial.print("Right x ");
    Serial.println(rx);
  }

  int ryd = ps2x.Analog(PSS_RY);
  if (ryd != ry) {
    ry = ryd;
    Serial.print("ry ");
    Serial.println(ry);
  }

  delay(75); // do not remove can cause trouble ;)
}
