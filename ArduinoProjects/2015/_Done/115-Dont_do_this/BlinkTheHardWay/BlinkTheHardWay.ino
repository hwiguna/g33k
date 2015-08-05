/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  //sbi(PORTA, PA5); //
  sbi(DDRA, PA5); // PA5 = output
}

// the loop function runs over and over again forever
void loop() {
  blinkN(3);
  delay(2000);
}

void blinkN(int howManyTimes)
{
  for (int i = 0; i < howManyTimes; i++)
  {
    sbi(PORTA, PA5); // set bit 5 of port a
    delay(200);              // wait for a second
    cbi(PORTA, PA5);   // turn the LED off by making the voltage LOW
    delay(200);              // wait for a second
  }
}


