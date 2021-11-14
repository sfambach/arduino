/*
  TCP Client

  initial sketch created by dlf 13 July 2010
  modified 31 May 2012 by Tom Igoe
  modified 19 Nov 2021 by Stefan Fambach
*/


#include <SPI.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>
#include "wifi_tools.h"
#include "arduino_secrets.h"

int keyIndex = 0;

/***************************************************************************************/
// gyrocopy & accelerator 
#include <MahonyAHRS.h>
Mahony filter;

float ax, ay, az;
float gx, gy,gz;
// float mx, my, mz // only if magnetometer is needed

/*
  the gyro's x,y,z values drift by a steady amount. if we measure this when arduino is still
  we can correct the drift when doing real measurements later
*/
//void calibrateIMU(int delayMillis, int calibrationMillis) {
//
//  int calibrationCount = 0;
//
//  delay(delayMillis); // to avoid shakes after pressing reset button
//
//  float sumX, sumY, sumZ;
//  int startTime = millis();
//  while (millis() < startTime + calibrationMillis) {
//    if (readIMU()) {
//      // in an ideal world gyroX/Y/Z == 0, anything higher or lower represents drift
//      sumX += gyroX;
//      sumY += gyroY;
//      sumZ += gyroZ;
//
//      calibrationCount++;
//    }
//  }
//
//  if (calibrationCount == 0) {
//    Serial.println("Failed to calibrate");
//  }
//
//  gyroDriftX = sumX / calibrationCount;
//  gyroDriftY = sumY / calibrationCount;
//  gyroDriftZ = sumZ / calibrationCount;
//
//}


bool readIMU() {
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() ) {
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);
    return true;
  }
  return false;
}

/***************************************************************************************/
// TCP/IP Client
WiFiClient client;

boolean checkServerConnection() {

  if (client.connected()) {
    return true;
  }

  Serial.print("Try to connect to server ");
  Serial.print(SERVER);
  Serial.print(" . ");
  Serial.println(PORT);
  if (client.connect(SERVER, PORT)) {
    Serial.println("connected to server");
    return true;
  } else {

    Serial.println("Connection to server failed");
    return false;
  }
}

/***************************************************************************************/
void setup() {

  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // -----------------------------------------------------
  // Start the gyrocope & acceleration detector
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

 // calibrateIMU(250,250);
 //  lastTime = micros();

}



void loop() {

  if (! checkWifiConnection()) {
    return;
  }

  if (!checkServerConnection()) {
    return;
  }




  // send gyroscopic data
  if (readIMU()) {

    // to radians 
    float gyroScale = 3.14159f / 180.0f;
    gx = gx * gyroScale;
    gy = gy * gyroScale;
    gz = gz * gyroScale;

  // Update the Mahony filter
    filter.updateIMU(gx, gy, gz, ax, ay, az);
    //filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);
    
    String s;
    s.reserve(100);
    s += "1;";
    s += filter.getPitch();
    s += ";";
    s += filter.getYaw();
    s += ";";
    s += filter.getRoll();

    

    Serial.println(s);
    client.println(s);

  }
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // I know delays are bad but this is only a test and
  // I do not want a message every millisecond, thats really to much
  //delay (2000);

}
