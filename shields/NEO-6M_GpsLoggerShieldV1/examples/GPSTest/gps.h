#include <TinyGPS++.h> // https://github.com/mikalhart/TinyGPSPlus
#include "credentials.h"
#include "debug.h"
#include <SoftwareSerial.h>
SoftwareSerial serial2(RXD2, TXD2); 


// The TinyGPS++ object
static TinyGPSPlus gps;
static boolean gpsConnected = false;

static void gpsGetData(unsigned long ms);
static String gpsGetLocation();



static void gpsSetup() {

 // pinMode(RXD2, INPUT);
 // pinMode(TXD2, OUTPUT);
  Serial.print(F("Serial2 connected RX/TX :"));
  Serial.print(RXD2);
  Serial.print(" / ");
  Serial.println(TXD2);
  serial2.begin(GPS_BOUD);
  delay(2000);
}


static void gpsLoop() {
  gpsGetData(3000);
}

static void gpsGetData(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (serial2.available()) {
      int i = serial2.read();
      //DEBUG_PRINT((char)i); // show received raw data 
      gps.encode(i);
    }
    //    while (softSerial.available()){
    //      gps.encode(softSerial.read());

  } while (millis() - start < ms);

  if (millis() > 5000 && gps.charsProcessed() < 10) {
    gpsConnected = false;
    DEBUG_PRINTLN(F("No GPS data received: check wiring"));
  } else {
    gpsConnected = true;
  }
}

static String gpsGetLocation() {
  String s;
  s.reserve(100);

  if (gps.location.isValid())
  {
    s = "lat/lng: ";
    s += gps.location.lat();
    s += " / ";
    s += gps.location.lng();
  } else {
    s = "lat/lng: NA / NA";
  }
  return s;
}

String gpsGetLng(int decimalPlaces){
  return String(gps.location.lng(),decimalPlaces);
}

String gpsGetLat(int decimalPlaces){
  return String(gps.location.lat(), decimalPlaces);
}

String gpsGetDate(){
   String s;
    s.reserve(11);
    
    s+= gps.date.month();
    s+= "/";
    s+= gps.date.day();
    s+= "/";
    s+= gps.date.year();
    return s;
}

String gpsGetTime(){
  String s;
    s.reserve(11);
    if (gps.time.hour() < 10){
      s+="0";
    }
    s+= gps.time.hour();
    s+=":";
    if (gps.time.minute() < 10){
      s+="0";
    }
    s+= gps.time.minute();
    s+=":";
    if (gps.time.second() < 10){
      s+= "0";
    }
   s+=gps.time.second();
//    s+=".";
//    if (gps.time.centisecond() < 10){
//      s+="0";
//    }
//    s+=gps.time.centisecond();
    return s;
}

static void gpsDisplayInfo()
{
#ifdef DEBUG
  if (!gpsConnected) {
    return;
  }

  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();

#endif // DEBUG

}
