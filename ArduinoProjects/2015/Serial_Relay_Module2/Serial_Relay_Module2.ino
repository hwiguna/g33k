/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

int bitPattern = 0xFF; // all bits on = off

void setup()
{
  Serial.begin(9600);
  Serial.println("hello");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.write( (byte)0x50);
  delay(1000);
}

void loop() // run over and over
{
  for (int i = 0; i < 8; i++) {
    Switch(i, 0); // On
    delay(2000);
    Switch(i, 1); // Off
  }
}

void Switch(byte which, byte state)
{
  mySerial.write( (byte)0x51);
  if (state == 1)
    bitPattern = bitSet(bitPattern, which);
  else
    bitPattern = bitClear(bitPattern, which);

  Serial.println(bitPattern, BIN);
  mySerial.write(bitPattern);
}

