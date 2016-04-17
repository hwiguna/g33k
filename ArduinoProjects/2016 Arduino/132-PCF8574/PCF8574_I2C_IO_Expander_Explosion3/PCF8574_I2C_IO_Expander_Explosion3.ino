// PCF8574 Explosion Demo (using same pin for Input AND Output)
// Hari Wiguna, 2016

#include <Wire.h>

uint8_t address;

void WriteIo(uint8_t bits)
{
  Wire.beginTransmission(address);
  Wire.write(bits);
  Wire.endTransmission();
}

uint8_t ReadIo()
{  
  WriteIo(B11111111); // PCF8574 require us to set all outputs to 1 before doing a read.
  
  Wire.beginTransmission(address);
  Wire.requestFrom((int)address, 1); // Ask for 1 byte from slave
  uint8_t bits = Wire.read(); // read that one byte
  Wire.endTransmission();
  
  return bits;
}

void ExplosionAnimation(uint8_t startAt)
{
  for (int i = 0; i < 8; i++)
  {
    uint8_t bits = B11111111; // All bits off

    // Turn on bits as long as it is not beyond our one byte "display"
    int lowerSide = startAt - i;
    int higherSide = startAt + i;
    if (lowerSide >= 0) bitClear(bits, lowerSide);
    if (higherSide <= 7) bitClear(bits, higherSide);

    WriteIo(bits); // Display the computed bit pattern
    delay(90); // Allow humans to see the bit pattern
    WriteIo(B11111111); // Erase "display"
  }
}

void setup() {
  Wire.begin(); // Arduino needs (SDA=A4,SCL=A5)
  //Wire.begin(0,2); // ESP8266 needs (SDA=GPIO0,SCL=GPIO2)
  address = 0x20;
}

void loop() {
  uint8_t bits = ReadIo(); // Read all switches

  //-- Don't do anything unless they press a switch --
  if ( bits != B11111111) // Unless they're all high...
  {
    //-- Find lowest pressed switch --
    for (byte bitIndex = 0; bitIndex < 8; bitIndex++)
      if (bitRead(bits, bitIndex) == 0) {
        ExplosionAnimation(bitIndex);
        exit;
      }    
  }
}
