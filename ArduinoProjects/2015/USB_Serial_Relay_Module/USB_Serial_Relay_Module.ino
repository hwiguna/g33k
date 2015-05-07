//
// I bought product below from IC Station and could not immediately find example code,
// so I decided to share this.
//
// ICStation 8 Channel MICRO USB Relay Module 5V ICSE014A
// http://www.icstation.com/icstation-channel-micro-relay-module-icse014a-p-5185.html
//
// Your fellow maker,
// Hari Wiguna

// Features:
// - Control 8 relays using only one or two GPIO pins
// - You can download a PC program to control it via USB
// - Relay contact up to 10A
// - 5V compatible, perfect to interface with Arduino

// Serial Protocol:
// At power up, module expects Arduino/PC to send 0x50
// Module would then send back an identifier: ICSE012A=0xAB, ICSE013A=0xAD, ICSE014A=0xAC
// Until this happens, module would not respond to other commands.
// To control the relays, we need to send 0x51 followed by another byte.
// the 8 bits in this byte corresponds with the 8 relays.
// WARNING: I was unable to set multiple bits to on AT ONCE. I believe this is because
// too much current is needed to do so.
// Instead, I was able to turn them one at a time within 10ms.  Inconvenient, but it works.

// Lessons learned:
// 1. DC Power jack does not work well. Maybe it's supposed to be for higher voltage?!
// 2. Relays take a lot of power, turning on multiple relays at once is unreliable.
// 3. Keep power supply for relay separate from Arduino

// Use software serial library so we won't affect the relay module while uploading sketch
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX.  Connect pin 11 to the RX on the relay module.

int bitPattern = 0xFF; // all 1s means all off
int prevIndex = 0;

void setup()
{
  Serial.begin(9600); // Open built-in RX/TX for debugging purpose.
  mySerial.begin(9600); // This is RX/TX for the relay modeul
  FindModule();
  delay(1000);
}

// When the module is powered up, it waits for 0x50 and sends back a device identifier.
// The module would be unresponsive to commands unless this had ocurred.
void FindModule()
{
  // Keep sending 0x50 until we receive a reply from module.
  while (!mySerial.available()) {
    delay(100);
    Serial.println("Relay Module are you there?");
    mySerial.write( (byte)0x50 ); // Relay module will send back acknowledgement
  }
  char c = mySerial.read(); // ICSE012A=0xAB, ICSE013A=0xAD, ICSE014A=0xAC
  Serial.print("YES! received: ");
  Serial.println(c, HEX);
}

void loop() // run over and over
{
  //OneAtATime();
  Blink();
  //Pot();
  //BackAndForth(20); // Parameter is delay in miliseconds. lower = faster.
  //MultipleBits(); // This routine does NOT work
}

// Blinks all 8 relays off and on
void Blink()
{
  AllOn();
  delay(1000);
  AllOff();
  delay(1000);
}

// Turns off all relays
void AllOff()
{
  for (int i = 0; i < 8; i++) {
    Switch(i, 1); // Off
    delay(5);
  }
}

// Turns ON all relays
void AllOn()
{
  for (int i = 0; i < 8; i++) {
    Switch(i, 0); // On
    delay(5);
  }
}

// Turns on one of the relays based on value of a potentiometer on Arduino Analog 0
void Pot()
{
  int index = map( analogRead(A0), 0, 1000 - 100, 0, 7);
  if (index != prevIndex) {
    Switch(prevIndex, 1); // Off
    delay(10);
    Switch(index, 0); // On
    delay(10);
    prevIndex = index;
  }
  delay(50);
}

// Test all 8 relays one at a time
void OneAtATime()
{
  for (int i = 0; i < 8; i++) {
    Switch(i, 0); // On
    delay(500);
    Switch(i, 1); // Off
    delay(5); // Give it some time before we send another command as the loop goes to next value.
  }
}

void BackAndForth(int delayMiliseconds)
{
  for (int i = 0; i < 8; i++) {
    Switch(i, 0); // On
    delay(delayMiliseconds);
    Switch(i, 1); // Off
    delay(5); // Give it some time before we send another command as the loop goes to next value.
  }
  for (int i = 7; i > 0; i--) {
    Switch(i, 0); // On
    delay(delayMiliseconds);
    Switch(i, 1); // Off
    delay(5); // Give it some time before we send another command as the loop goes to next value.
  }
}


// Specify which relay to control (0..7)
// and whether to turn it off/on.
// Set state to 1 to turn it OFF
// Set state to 0 to turn it ON
void Switch(byte which, byte state)
{
  mySerial.write( (byte)0x51);
  if (state == 1) {
    //bitPattern = 0xFF;
    bitPattern = bitSet(bitPattern, which);
  }
  else {
    //bitPattern = 0x00;
    bitPattern = bitClear(bitPattern, which);
  }

  Serial.println(bitPattern, BIN);
  mySerial.write( (byte)bitPattern);
}

// This does NOT work.  Presumably because there is not enough current
// to power all relays at the exact same time.
// Use AllOn() or AllOff() routines instead.
void MultipleBits()
{
  int pattern = 0xFF;
  mySerial.write( (byte)0x51);
  mySerial.write( (byte)pattern);
  Serial.println(pattern, BIN);

  delay(1000);
  pattern = 0x00;
  mySerial.write( (byte)0x51);
  mySerial.write( (byte)pattern); // ON
  Serial.println(0x00, BIN);

  delay(1000);
}


