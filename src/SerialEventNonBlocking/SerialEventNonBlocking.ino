/** Test the Serial Event
 *  Read data in the event and print it when its finished
 *  Autor: S. Fambach
 *  Visit http://www.fambach.net if you want
*/


boolean stringComplete = false;
String serialInput;

/**
   Remove sting to the first occurance of \n
*/
String getFirstInput() {
  int index = serialInput.indexOf("\n");
  String ret = serialInput.substring(0, index);
  // remove also the new line
  serialInput.remove(0, index + 1);
  stringComplete = false;
  return ret;
}

void setup() {

  // start the serial
  Serial.begin(115200);

  // reserve some memmory for the string
  serialInput.reserve(50);
}

void loop() {

  // if there is a finished input do something
  if ( stringComplete ) {
    Serial.print("Received: ");
    Serial.println(getFirstInput());

  }
}

/**
    serial event function will be called after the loop automatically

*/
void serialEvent() {

  // read something
  if(Serial.available()){
     char inChar = (char)Serial.read();
     // add it to the inputString:
     serialInput += inChar;

     if (inChar == '\n' ) {
       stringComplete = true;

     }
  }
}
