#include <AFMotor.h>
#include <Servo.h> 


// server
#define PING "0001"
#define CONFIRM "0002"
#define COMPASS "0010"
#define ACCESSPOINT "0020"
#define DISTANCE "0030"
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

// DC motor on M2
AF_DCMotor mright(2);
// DC motor on M3
AF_DCMotor mleft(1);
 


/***********************************************/
/* Distance mesurement                         */
/***********************************************/ 


// dist
#define echoPin A2 // Echo Pin D3
#define trigPin A3 // Trigger Pin D4
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed

void initSR40(){
   Serial.print("Init SR-40");
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   Serial.print("Init SR-40 .... success");
}

long readDistance(){

    /* The following trigPin/echoPin cycle is used to determine the
     distance of the nearest object by bouncing soundwaves off of it. */ 
    long distance,duration;  // Duration used to calculate distance
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 
    
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
     
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
     
    //Calculate the distance (in cm) based on the speed of sound.
    distance = duration/58.2;

    return distance;
}

 
void setup() 
{ 
  Serial.begin(115200);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 

  mright.setSpeed(200);
  mright.run(RELEASE);

  mleft.setSpeed(500);
  mleft.run(RELEASE);

  initSR40();
} 
int step = 10;
const int MIN = 50, 
          MAX = 150, 
          MAX_SPEED = 250, 
          TURN_SPEED=200,
          MIN_DIST=25,
          CENTER = 100, 
          CENTER_LEFT=100+step, 
          CENTER_RIGHT= 100-step;

int pos = MIN;    // variable to store the servo position 

void loop() 
{ 
    Serial.print("Distance measurement:\t");
    long dist = readDistance();
   
    Serial.print("[");
    Serial.print(pos);
    Serial.print("#,");
    Serial.print(dist);
    Serial.print("]");

    if(dist < MIN_DIST) {
      
      if( pos < CENTER_RIGHT){ // anstross rechts also drehe nach links
        Serial.print("TL");
        mright.run(FORWARD);  
        mleft.run(BACKWARD);  
        mright.setSpeed(TURN_SPEED);  
        mleft.setSpeed(TURN_SPEED); 
        
      } else if( pos > CENTER_LEFT){ // anstoss links als drehe nach rechts
        Serial.print("TR");
        //mright.run(BACKWARD);  
        //mleft.run(FORWARD);  

        mright.run(FORWARD);  
        mleft.run(BACKWARD);  

        mright.setSpeed(TURN_SPEED);  
        mleft.setSpeed(TURN_SPEED); 

      } else { // irgendwo in der mitte also fahr mal zurück
        mright.run(BACKWARD);  
        mleft.run(BACKWARD);  

        mright.setSpeed(TURN_SPEED);  
        mleft.setSpeed(TURN_SPEED); 
      }
      
    } else {
      Serial.print("FW");
      mright.run(FORWARD);  
      mleft.run(FORWARD);  

      mright.setSpeed(MAX_SPEED);  
      mleft.setSpeed(MAX_SPEED); 

      // pos und richtung neu berechnen
      pos +=step; 
      if( pos < MIN || pos > MAX){ 
        step *= -1;
      }
  
      // servo auf neue pos setzen
      myservo.write(pos); 
      delay(10);
        
    }  
      
    Serial.print("|\t");
    Serial.println();
}

