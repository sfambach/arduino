String buf = "";

void setup(){
  Serial.begin(9600);
  while(!Serial){ delay(1);}
  buf.reserve(200);
  Serial.println("UNO started");
}

int ib = 0;
void loop(){
  while (Serial.available()){
    delay(4); // allow buffer to fill
    ib = Serial.read();
    buf += ((char)ib);

    if(((char)ib)== '\n' || buf.length()== 200){
        Serial.print("Echo: ");
        Serial.print(buf);
        buf = "";
    }
  }
}

