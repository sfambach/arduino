/*
  Front Motor (Steering) => Channel A
 Back Motor => Channel B
 
 Since the motor shield hijacks 6 pins for the motors'
 control, they are declared in the MotorShieldR3 library.
 */
#define PWM1_PIN    10
#define DIR1_PIN    12
#define PWM2_PIN    11
#define DIR2_PIN    13

char command = 'S';
int minSpeed = 150;   
int velocity = minSpeed;
void setup() 
{       
  Serial.begin(9800);  //Set the baud rate to that of your Bluetooth module.

  // init motor pins
  pinMode( PWM1_PIN, OUTPUT);
  pinMode( DIR1_PIN, OUTPUT);
  pinMode( PWM2_PIN, OUTPUT);
  pinMode( DIR2_PIN, OUTPUT);

  
}


void forward(){

    digitalWrite(DIR1_PIN, LOW);
    digitalWrite(DIR2_PIN, LOW);
    analogWrite(PWM1_PIN, velocity);
    analogWrite(PWM2_PIN, velocity);
}

void backward(){

    digitalWrite(DIR1_PIN, HIGH);
    digitalWrite(DIR2_PIN, HIGH);
    analogWrite(PWM1_PIN, velocity);
    analogWrite(PWM2_PIN, velocity);
}



void fr(){

    digitalWrite(DIR1_PIN, LOW);
    digitalWrite(DIR2_PIN, LOW);
    analogWrite(PWM1_PIN, velocity/2);
    analogWrite(PWM2_PIN, velocity);
}

void fl(){

    digitalWrite(DIR1_PIN, LOW);
    digitalWrite(DIR2_PIN, LOW);
    analogWrite(PWM1_PIN, velocity);
    analogWrite(PWM2_PIN, velocity/2);
}


void br(){

    digitalWrite(DIR1_PIN, HIGH);
    digitalWrite(DIR2_PIN, HIGH);
    analogWrite(PWM1_PIN, velocity/2);
    analogWrite(PWM2_PIN, velocity);
}

void bl(){

    digitalWrite(DIR1_PIN, HIGH);
    digitalWrite(DIR2_PIN, HIGH);
    analogWrite(PWM1_PIN, velocity);
    analogWrite(PWM2_PIN, velocity/2);
}

void turnRight(){
    digitalWrite(DIR1_PIN, HIGH);
    digitalWrite(DIR2_PIN, LOW);
    analogWrite(PWM1_PIN, minSpeed);
    analogWrite(PWM2_PIN, minSpeed);
}

void turnLeft(){
    digitalWrite(DIR1_PIN, LOW);
    digitalWrite(DIR2_PIN, HIGH); 
    analogWrite(PWM1_PIN, minSpeed);
    analogWrite(PWM2_PIN, minSpeed);
}

void stopCar(){
  analogWrite(PWM1_PIN, 0);
  analogWrite(PWM2_PIN, 0);
}


void loop(){
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    //Change pin mode only if new command is different from previous.   
    //Serial.println(command);
    switch(command){
    case 'F':  
      forward();
      break;
    case 'B':  
      backward();
      break;
    case 'L':  
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'S':  
      stopCar();
      break; 
    case 'I':  //FR  
      fr();
      break; 
    case 'J':  //BR  
      br();
      break;        
    case 'G':  //FL  
      fl();
      break; 
    case 'H':  //BL
      bl();
      break;
    case 'W':  //Font ON 
      //digitalWrite(pinfrontLights, HIGH);
      break;
    case 'w':  //Font OFF
      //digitalWrite(pinfrontLights, LOW);
      break;
    case 'U':  //Back ON 
      //digitalWrite(pinbackLights, HIGH);
      break;
    case 'u':  //Back OFF 
      //digitalWrite(pinbackLights, LOW);
      break; 
    case 'D':  //Everything OFF 
    //  digitalWrite(pinfrontLights, LOW);
    //  digitalWrite(pinbackLights, LOW);
     stopCar();
      break;         
    default:  //Get velocity
      if(command=='q'){
        velocity = 255;  //Full velocity
       // yellowCar.SetSpeed_4W(velocity);
        
      } else{ 
        //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
        if((command >= 48) && (command <= 57)){ 
          //Subtracting 48 changes the range from 48-57 to 0-9.
          //Multiplying by 25 changes the range from 0-9 to 0-225.
          velocity = minSpeed +((command - 48)*10);       
          // yellowCar.SetSpeed_4W(velocity);
        }
      }
    }
  } 
}
