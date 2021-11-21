/***********************************************
 * Control pan/tilt with joystick
 * www.fambach.net
 * GPL v2
 */
#include<Servo.h>


#define JOYX A0
#define JOYY A1
Servo servox;
Servo servoy;

void setup(){
  Serial.begin(115200);
  servox.attach(9);
  servoy.attach(10);
  
}

int xmin = 20, xmax = 130, ymin = 0, ymax = 125, step = 10; 
void loop(){

int ax = analogRead(JOYX);
int ay = analogRead(JOYY);
  int x = map(ax, 1024,0, xmin, xmax);
  int y = map(ay, 0,1024, ymin, ymax);

  servox.write(x);
  servoy.write(y);


  Serial.print("aX: ");
  Serial.print(ax);
  Serial.print(" aY: ");
  Serial.print(ay);

  Serial.print(" sX: ");
  Serial.print(x);
  Serial.print(" sY: ");
  Serial.print(y);

  Serial.println();

}

