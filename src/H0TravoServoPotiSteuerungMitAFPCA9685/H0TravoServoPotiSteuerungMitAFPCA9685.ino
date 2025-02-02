/******************************************************************************
# Description
Control for Servos via adjustable resitors
It can control up to 16 servos with an Arduino Mega.

## Settings
Setup in the code below
* SERVOMIN
* SERVOMAX
* POTI_INPUTS
* POTI_COUNT
* THESHOLD

## Libs
https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library

## Hardware 
* Arduino Mega
* PCA9685 16 Channel Servo Driver

## Credits 
* Licence: AGPL3
* Author:  S. Fambach
Visit http://www.fambach.net if you want
******************************************************************************/
#include <Arduino.h>
#include <Wire.h> 

/*****************************************************************************/
// Debuging

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif


char buffer[130];
/*****************************************************************************/
// setup for servos 

/** die Adafruit bibliothek angeben bitte vorher installieren
* https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
* und einige Werte vordefinieren
*/
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // Objekt zur Ansteuerung der Platine

const uint16_t USMIN = 570; // 600 - Minimaler wert für den Servo in Microsekunden, bitte mit deinen Servos ausprobieren.
const uint16_t USMAX = 2160; // 2400 - Maximaler Wert für den Servo, auch ausprobieren
#define SERVO_FREQ 50 // Servo Frequenz - Analog servos run at ~50 Hz updates

/*****************************************************************************/
// Setup for potis 

/** alle Eingangspins */
const uint8_t POTI_INPUTS[] = {A0,A1,A2,A3,A4,A5,A5,A7,A8,A9,A10,A11,A12,A13,A14,A15}; 
uint16_t poti_last_value[]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/** Anzahl der genutzten potis muss der anzahl der Einträge im Array POTI_INPUTS ergeben.*/
const uint8_t POTI_COUNT = 16; // 

/* Damit die servos nicht hin und herspringen, wird nur was geändert wenn 
* der Wert sich um +/- THRESHOLD unterscheidet zu hohe Werte lassen die 
* Einstellungen ungenau werden zu kleine Werte führe zum Springen der Servos
*/
const uint8_t THRESHOLD = 2; 

const uint16_t POTI_MAX_READ = 1024; // 1024 for 10 Bit ADC and 4096 for 12 bit ADC



/*****************************************************************************/
// main program 

void setup() {
  // seriellen Port für Ausgaben starten
  Serial.begin(9600);
  
  // schauen ob das board angeschlossen ist
  DEBUG_PRINTLN("Check Board");
  Wire.begin();
  Wire.beginTransmission (0x40);
  if (Wire.endTransmission () == 0)
  {
    DEBUG_PRINTLN("Board found");
  } else {
    DEBUG_PRINTLN("Board NOT found, check wiring");
    while(1);
  } 
  

  // board starten
  pwm.begin();
  
    /* Frequenz berechnen/setzen
   * In theory the internal oscillator (clock) is 25MHz but it really isn't
   * that precise. You can 'calibrate' this by tweaking this number until
   * you get the PWM update frequency you're expecting!
   * The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
   * is used for calculating things like writeMicroseconds()
   * Analog servos run at ~50 Hz updates, It is importaint to use an
   * oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
   * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
   *    the I2C PCA9685 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
   *    expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9685 chip and
   * affects the calculations for the PWM update frequency. 
   * Failure to correctly set the int.osc value will cause unexpected PWM results
   */
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates


  delay(100); // gib dem Ganzen Zeit und lass es kurz ruhen ;)

}  // end of setup

void loop() {

  // frage alle potis nacheinander ab
  for(int potiNum = 0; potiNum < POTI_COUNT; potiNum++) {
    
    uint16_t currentPotiValue = analogRead(POTI_INPUTS[potiNum]);
    // nur servo schalten wenn der wert größer dem threshold ist
    if( currentPotiValue < poti_last_value[potiNum] - THRESHOLD || 
        currentPotiValue > poti_last_value[potiNum] + THRESHOLD ){

      // servo wert berechnen, ich verwende dazu die map funktion von arduino
      // rechnet die Poti werte auf die servos ms um map(value, fromLow, fromHigh, toLow, toHigh)
      uint16_t currentServoValue = map(currentPotiValue, 0,POTI_MAX_READ, USMIN, USMAX);
      // servo stellen
      pwm.writeMicroseconds(potiNum, currentServoValue);     

      // ausgabe 
#ifdef DEBUG
      sprintf(buffer,"Servo %i Value[old/new] %i / %i Servo [ms] %i",potiNum,poti_last_value[potiNum],currentPotiValue, currentServoValue);
      DEBUG_PRINTLN(buffer);
#endif
      // neuen Wert speichern
      poti_last_value[potiNum]  = currentPotiValue;


    }

  }

  delay(100); // gib dem Ganzen Zeit und lass es kurz ruhen ;)
}

















 
