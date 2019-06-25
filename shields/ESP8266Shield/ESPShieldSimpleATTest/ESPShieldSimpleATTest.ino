#include <SoftwareSerial.h>

SoftwareSerial swser(2, 3);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(2000); // wait some time

  swser.begin(115200);
  // switch to 9600 Boud its more save for software serial
  swser.print("AT+UART_CUR=9600,8,1,0,0\r\n");
  swser.begin(9600);

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, false);

  // send AT command
  swser.flush();
  swser.print("AT\r\n");
  Serial.print("AT ");
  delay(400);

  // receive answer
  String result;
  result.reserve(50);
  while (!swser.available() > 0) {
    Serial.print(".");
    delay(100);
  }

  // remove some special characters
  result = swser.readString();
  result.replace("\n" , "");
  result.replace("\r" , "");
  result.replace("\0x18" , " ");

  // check the result
  if (result.endsWith("OK")) {
    digitalWrite(LED_BUILTIN, true);
    Serial.println(result);
  } else {
    Serial.println(result);
    Serial.println(" NOK");
  }
  delay(2000);
}
