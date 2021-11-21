#include <Adafruit_HMC5883_U.h>

#define CONFIRM "0002"
Adafruit_HMC5883_Unified compass = Adafruit_HMC5883_Unified(12345);

int minx= 65535;
int miny= 65535;
int maxx = 0;
int maxy = 0;
int corx = 0;
int cory = 0;

void initHMC5883(){
   /* Initialise the sensor */
  Serial.println("Init Sensor HMC5883");
  //compass.setMagGain()
  if(!compass.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
}


String readHMC5883(){
/* Get a new sensor event */ 
  sensors_event_t event; 
  compass.getEvent(&event);


  if(minx > event.magnetic.x){
    minx = event.magnetic.x; 
  }else if(maxx < event.magnetic.x){
    maxx=event.magnetic.x; 
  }

   if(miny > event.magnetic.y){
    miny = event.magnetic.y; 
  }else if(maxy < event.magnetic.y){
    maxy=event.magnetic.y; 
  }

  // calculate correction
  corx = (minx+maxx)/2;
  cory = (miny+maxy)/2;

  event.magnetic.x -= corx; 
  event.magnetic.y -= cory; 
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  //Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  //Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  //Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = 0.0349066; // 0.22;
  heading += declinationAngle;
 //heading -= 0.785;
 // heading-=35;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  
  //h %= 359;
  
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);

  String s = "";
  s.concat(heading);
  s.concat(";");
  s.concat(headingDegrees);
  s.concat(";");
  s.concat(event.magnetic.x);
  s.concat(";");
  s.concat(event.magnetic.y);
  s.concat(";");
  s.concat(event.magnetic.z);
  s.concat("]\n");

  return s;
}

void setup() {
  initHMC5883();

}

void loop() {
  Serial.println(readHMC5883());
  delay(2000);

}


