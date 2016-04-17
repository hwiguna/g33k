// PCF8574 Explosion Demo (using same pin for Input AND Output)
// Hari Wiguna, 2016

#include <Wire.h>

uint8_t address, curVal, val;

void WriteI2C(uint8_t bits)
{
  Wire.beginTransmission(address);
  Wire.write(bits);
  Wire.endTransmission();
}

uint8_t ReadI2C()
{
  Wire.beginTransmission( address );
  Wire.requestFrom((int)address, 1); // Ask for 1 byte from slave
  uint8_t bits = Wire.read(); // read that one byte
  Wire.endTransmission();
  return bits;
}

void ExplosionAnimation(uint8_t sw)
{
  for (int i = 0; i < 8; i++)
  {
    uint8_t oo = 0xFF; // All bits off

    // Turn on bits as long as it is not beyond our one byte "display"
    int left = sw - i;
    int rite = sw + i;
    if (left >= 0) bitClear(oo, left);
    if (rite <= 7) bitClear(oo, rite);

    WriteI2C(oo); // Display the computed bit pattern
    delay(90); // Allow humans to see the bit pattern
    WriteI2C(0xFF); // Erase "display"
  }
}

void setup() {
  Wire.begin(); // Arduino needs (SDA=A4,SCL=A5)
  //Wire.begin(0,2); // ESP8266 needs (SDA=GPIO0,SCL=GPIO2)
  address = 0x20;
  curVal = 0xFF; // all off
}

void loop() {
  WriteI2C(0xFF); // To read we need to first set all outputs to HIGH
  val = ReadI2C(); // Read all switches

  //-- Don't do anything unless they press a switch --
  if ( val != 0xFF) // Unless they're all high...
  {
    curVal ^= ~val;  // Invert every switch that is pressed (LOW).

    while ( val != 0xFF ) val = ReadI2C(); // Wait for button release

    //-- Find lowest pressed switch --
    int sw = -1;
    for (byte b = 0; b < 8; b++)
      if (bitRead(curVal, b) == 0) {
        sw = b;
        curVal = 0xFF;
        exit;
      }

    //=== Explode ===
    if (sw != -1) ExplosionAnimation(sw);
  }
}

