// PCF8574 Explosion Demo (using same pin for Input AND Output)
// Hari Wiguna, 2016

#include <Wire.h>

uint8_t error, address, curVal, val;

void ExplosionDemo()
{
  //-- To read we need to first set all outputs to HIGH --
  Wire.beginTransmission(address);
  Wire.write(0xFF); // Get ready to read all bits
  error = Wire.endTransmission();

  //-- Read all switches --
  Wire.beginTransmission( address );
  Wire.requestFrom((int)address, 1); // Ask for 1 byte from slave
  val = Wire.read(); // read that one byte
  error = Wire.endTransmission();

  //-- Don't do anything unless they press a switch --
  if ( val != 0xFF) // Unless they're all high...
  {
    curVal ^= ~val;  // Invert every switch that is pressed (LOW).

    //-- Wait for button release --
    while ( val != 0xFF )
    {
      Wire.beginTransmission( address );
      Wire.requestFrom((int)address, 1); // Ask for 1 byte from slave
      val = Wire.read(); // read that one byte
      error = Wire.endTransmission();
    }

    //-- Find lowest pressed switch --
    int sw = -1;
    for (byte b = 0; b < 8; b++)
      if (bitRead(curVal, b) == 0) {
        sw = b;
        curVal = 0xFF;
        exit;
      }

    //=== Explode ===
    if (sw != -1)
      for (int i = 0; i < 8; i++)
      {
        uint8_t oo = 0xFF; // All bits off

        // Turn on bits as long as it is not beyond our one byte "display"
        int left = sw - i;
        int rite = sw + i;
        if (left >= 0)  bitClear(oo, left);
        if (rite <= 7)  bitClear(oo, rite);

        //-- Display the computed bit pattern --
        Wire.beginTransmission(address);
        Wire.write(oo);
        error = Wire.endTransmission();

        delay(90); // Allow humans to see the bit pattern

        //-- Erase "display" --
        Wire.beginTransmission(address);
        Wire.write(0xFF);
        error = Wire.endTransmission();
      }
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Arduino needs (SDA=A4,SCL=A5)
  //Wire.begin(0,2); // ESP8266 needs (SDA=GPIO0,SCL=GPIO2)
  address = 0x20;
  curVal = 0xFF; // all off
}

void loop() {
  ExplosionDemo();
}

