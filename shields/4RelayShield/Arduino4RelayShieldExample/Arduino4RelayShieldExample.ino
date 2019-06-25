/** 4 Relay shield test
 *  www.fambach.net
 *  GPLv2
 */

// define the pins for the relays
#define RELAY_1 7 
#define RELAY_2 6 
#define RELAY_3 5 
#define RELAY_4 4 

// delay between switches
#define DELAY 1000

// array to access it in a for loop
const uint8_t relays[]={RELAY_1, RELAY_2, RELAY_3, RELAY_4};

void setup() {
  Serial.begin(115200);
  
  // init ios
  for(int i = 0; i < sizeof(relays); i++){
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], false);
    Serial.print(F("Set Relay "));
    Serial.print(i);
    Serial.println(F(" to OUTPUT"));
  }
}

void loop() {
  
  // swith on one ofter another
  for(int i = 0; i < sizeof(relays); i++){
    digitalWrite(relays[i], true);
    Serial.print(F("Switch Relay "));
    Serial.print(i);
    Serial.println(F(" ON"));
    delay(DELAY);
  }

  // switch off one after another in the oposite direction
  for(int i = sizeof(relays)-1; i >=0  ; i--){
    digitalWrite(relays[i], false);
    Serial.print(F("Switch Relay "));
    Serial.print(i);
    Serial.println(F(" OFF"));
    delay(DELAY);
  }

  // all on 
  Serial.println(F("All OFF"));
  for(int i = 0; i < sizeof(relays); i++){
    digitalWrite(relays[i], true);
  }
  delay(DELAY);
  
  // all off
  Serial.println(F("All OFF"));
  for(int i = 0; i < sizeof(relays); i++){
    digitalWrite(relays[i], false);
  }
  delay(DELAY);
  
}
