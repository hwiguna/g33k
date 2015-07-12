// ICStation 8 Channel MICRO USB Relay Module 5V ICSE014A
// http://www.icstation.com/icstation-channel-micro-relay-module-icse014a-p-5185.html
//
// I bought the above product from IC Station and could not immediately find example code,
// so I decided to share this.
// Your fellow maker,
// Hari Wiguna

// v2 this one only works (I think it's because only one relay is on at one time)
// v3 this works as long as we power off, unplug usb, and then power up using 2A psu on the arduino vIN

// Use software serial library so we won't affect the relay module while uploading sketch
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX.  Connect pin 11 to the RX on the relay module.

// module always sends the states of ALL relays at once, so we'll keep all current states here.
int bitPattern = 0xFF; // all bits on = off

void setup()
{
  Serial.begin(9600); // Open built-in RX/TX for debugging purpose.
  mySerial.begin(9600); // This is RX/TX for the relay modeul

  while (!mySerial.available()) {
    delay(100);
    Serial.println("Relay Module are you there?");
    mySerial.write( (byte)0x50 ); // Relay module will send back acknowledgement
  }
  char c = mySerial.read(); // ICSE012A=0xAB, ICSE013A=0xAD, ICSE014A=0xAC
  Serial.print("YES! received: ");
  Serial.println(c, HEX);
  delay(1000);

  //  bitPattern = 0xFF;
  //  Serial.print( "Send pattern to relays: ");
  //  Serial.println( bitPattern, BIN);
  //  mySerial.write( (byte)0x51);
  //  mySerial.write(bitPattern);
  //  delay(1000);

  //  bitPattern = 0xFF -16 -32 ; //-4 -8; // -1 -2 -4;
  //  Serial.print( "Send pattern to relays: ");
  //  Serial.println( bitPattern, BIN);
  //  mySerial.write( (byte)0x51); delay(50);
  //  mySerial.write(bitPattern);
  //  delay(1000);

  // Switch(0, 1); delay(1000);
  // Switch(1, 1); delay(1000);
  // Switch(2, 1); delay(1000);
  // Switch(3, 1); delay(1000);
  // Switch(4, 1); delay(1000);
  // Switch(5, 1); delay(1000);
  // Switch(6, 1); delay(1000);
  //Switch(7, 0); delay(1000);

//  AllOff(); delay(1000);
//  Switch(0, 0); delay(1000);
//  Switch(1, 0); delay(1000);
//  Switch(2, 0); delay(1000);
//  Switch(3, 0); delay(1000);
//  Switch(4, 0); delay(1000);
//  Switch(5, 0); delay(1000);
//  Switch(6, 0); delay(1000);
//  Switch(7, 0); delay(1000);
}

void loop() // run over and over
{
  //OneAtATime();
  //MultipleBits();
  AllOn();
  delay(1000);
  AllOff();
  delay(1000);
}

void AllOff()
{
  for (int i = 0; i < 8; i++) {
    Switch(i, 1); // Off
    delay(10);
  }
}

void AllOn()
{
  for (int i = 0; i < 8; i++) {
    Switch(i, 0); // On
    delay(10);
  }
}

void MultipleBits()
{
  byte pattern = 0xFF;
  mySerial.write( (byte)0x51);
  mySerial.write( (byte)pattern);
  Serial.println(pattern, BIN);

  delay(500);
  mySerial.write( (byte)0x51);
  mySerial.write( (byte)0x00); // ON
  Serial.println(0x00, BIN);

  delay(1000);
}

void OneAtATime()
{
  for (int i = 0; i < 8; i++) {
    Switch(i, 0); // On
    delay(1000);
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
  mySerial.write( (byte)bitPattern);
}

