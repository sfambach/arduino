#include "DHT.h" //DHT Bibliothek laden

#define DHTPIN GPIO5        // Pin auf dem Arduino
#define DHTTYPE DHT11   // Typ des Sensors

DHT dht(DHTPIN, DHTTYPE); // Eine Instanz des Sensors erstellen

void setup() {
  Serial.begin(9600); 
  dht.begin(); //DHT11 Sensor starten
}

void loop() {
  
  delay(2000); //Zwei Sekunden Vorlaufzeit bis zur Messung (der Sensor ist etwas träge)

  float wett = dht.readHumidity(); //die Luftfeuchtigkeit auslesen
  float temp = dht.readTemperature();//die Temperatur auslesen 
  Serial.print("Luftfeuchtigkeit: "); //Im seriellen Monitor den Text und 
  Serial.print(wett); //die Dazugehörigen Werte anzeigen
  Serial.print(" % \t");
  Serial.print("Temperatur: ");
  Serial.print(temp);
  Serial.println(" Grad Celsius");

}
