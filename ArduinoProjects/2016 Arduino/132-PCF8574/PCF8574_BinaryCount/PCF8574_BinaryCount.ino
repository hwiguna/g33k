// PCF8574 Binary Counter Test
// Hari Wiguna, 2016

#include <Wire.h>

uint8_t address = 0x21;

void BinaryCountTest()
{
  for (uint8_t val = 0; val <= 255; val++)
  {
    Serial.print(val);
    Serial.print(" ");
    Wire.beginTransmission(address);
    Wire.write(~val);
    uint8_t error = Wire.endTransmission();
    Serial.println(error);
    delay(200);
  }
}

void setup() {
  Serial.begin(9600);
  
  //Wire.begin(); // Arduino needs (SDA=A4,SCL=A5)
  Wire.begin(0,2); // ESP8266 needs (SDA=GPIO0,SCL=GPIO2)
}

void loop() {
  BinaryCountTest();
}
