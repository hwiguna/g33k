#include <Wire.h>

int mode = 0;
uint8_t error, address, curVal, val;

void OutputDemo()
{
  for (val = 0; val <= 127; val++)
  {
    Serial.print(val);
    Serial.print(" ");
    Wire.beginTransmission(address);
    Wire.write(~val);
    error = Wire.endTransmission();
    Serial.println(error);
    delay(500);
  }
}

void InputDemo()
{
  Wire.beginTransmission( address );
  Wire.write(0xFF); // Get ready to read all bits
  Wire.requestFrom((int)address, 1); // Ask for 1 byte from slave
  val = ~Wire.read(); // read that one byte
  error = Wire.endTransmission();
  Serial.print(val, BIN);
  Serial.print(" ");
  Serial.println(error);
  delay(500);
}

void IODemo()
{
  //-- Input --
  Wire.beginTransmission( address );
  Wire.write(0xFF); // Get ready to read all bits
  Wire.requestFrom((int)address, 1); // Ask for 1 byte from slave
  val = Wire.read(); // read that one byte
  error = Wire.endTransmission();

  Serial.println(val, BIN);
  
  //-- Process --
  uint8_t newVal = 0x0F;
  if (bitRead(val,3) == 0) bitClear(newVal,7); else bitSet(newVal,7);
  if (bitRead(val,2) == 0) bitClear(newVal,6); else bitSet(newVal,6);
  if (bitRead(val,1) == 0) bitClear(newVal,5); else bitSet(newVal,5);
  if (bitRead(val,0) == 0) bitClear(newVal,4); else bitSet(newVal,4);

  //-- Output --
  Wire.beginTransmission(address);
  Wire.write(newVal);
  error = Wire.endTransmission();
  delay(10); // let humans 
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  address = 0x20;
  curVal = 0x02;

  //OutputDemo();
}

void loop() {
  //InputDemo();
  IODemo();
}

//  //-- Show current bit states --
//  Wire.beginTransmission( address );
//  Wire.write(~curVal);
//  error = Wire.endTransmission();
//delay(2000);
//  Serial.println("Waiting for keypress..");
//
//  //do
//  {
//    Wire.beginTransmission( address );
//    Wire.write(0xFF); // Get ready to read all bits
//    Wire.requestFrom((int)address, 1); // Ask for 1 byte from slave
//    val = Wire.read(); // read that one byte
//    error = Wire.endTransmission();
//
//    Wire.beginTransmission( address );
//    Wire.write(~curVal);
//    error = Wire.endTransmission();
//
//  } //while (val == 0xFF);
//
//  Serial.print(val, BIN);
//  Serial.print(" ");
//
//  for (byte b = 0; b < 8; b++)
//  {
//    if (bitRead(val, b) == 0) {
//      Serial.print("* ");
//      if (bitRead(curVal, b) == 0) {
//        bitSet(curVal, b);
//      }
//      else {
//        bitClear(curVal, b);
//      }
//      delay(1000);
//    }
//  }
//
//  Serial.println(curVal, BIN);
//  delay(500);


