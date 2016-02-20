#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  
//#define DHTTYPE DHT21   // DHT 21 
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
}
void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
 Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println();
  //Serial.print(" %\t");
  Serial.print("Temperature: ");
Serial.print(f);
  Serial.print(" *F\t");
Serial.println();
Serial.println();
}
