#include <Wire.h>

uint8_t error, address, val;

void setup() {
  pinMode(13,OUTPUT);
  Wire.begin();

  Serial.begin(9600);

  address = 0x20;
  val = 0x00;

  //-- Must set all outputs to high before using it as input --
  Wire.beginTransmission(  (0x20) );
  Wire.write(val);
  error = Wire.endTransmission();

}

void loop() {
  Wire.beginTransmission( address );
  Wire.write(0x01);
  Wire.requestFrom((int)address, 1); // Ask for 1 byte from slave
  val = Wire.read(); // read that one byte
  error = Wire.endTransmission();
Serial.println(val);
  digitalWrite(13, (val & 0x01));
  delay(10);
}

// put your main code here, to run repeatedly:
//  for (val = 0; val < 127; val++)
//  {
//    Wire.beginTransmission(  (0x20) );
//    Wire.write(val);             // sends value byte
//    error = Wire.endTransmission();
//    Serial.println(error);
//
//    delay(500);
//  }
