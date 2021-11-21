#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
}

int xmin = 32767, ymin = 32767, xmax= -32768, ymax = -32768;
void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
//  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
//  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
//  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

String s = "#"+String((int)event.magnetic.x)+";"+String((int)event.magnetic.y);
Serial.println(s);

  if(event.magnetic.x > xmax) xmax = event.magnetic.x ;
  if(event.magnetic.x < xmin) xmin = event.magnetic.x ;
  if(event.magnetic.y > ymax) ymax = event.magnetic.y ;
  if(event.magnetic.y < ymin) ymin = event.magnetic.y ;

// Serial.print("Extrema: (xmin/ymin/xmax/ymax)"); Serial.print(xmin); Serial.print(" / ");Serial.print(ymin); Serial.print(" / ");Serial.print(xmax); Serial.print(" / ");Serial.print(ymax); Serial.println(" ");

  // calculate center
  int xc = (xmax+xmin)/2;
  int yc = (ymax+ymin)/2;

//  Serial.print("Calculated center: "); Serial.print(xc); Serial.print(" / ");Serial.println(yc);

  

  //float heading = atan2(event.magnetic.y-yc, event.magnetic.x-xc);
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle =  0.0349066;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
  
  delay(500);
}
