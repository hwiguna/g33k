// v01 - Blink using direct port manipulation
// v02 - read button using direct port manipulation
// v03 - Blink n times based on which button is pressed
// v04 - Read buttons using interrupt instead of polling in loop()

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

const byte button0 = PD2;
const byte button1 = PD3;
const byte button2 = PD4;

void setup() {
  sbi(DDRB, PB5); // Pin D13 (PB5) as output
  cbi(DDRD, button0); // D2 (PD2) as input
  
  sbi(SREG,SREG_I); // Enable global interrupt
}

void loop() {
  byte vals = PIND;
  if (bitRead(vals, button0)==0) Blink(1);
  if (bitRead(vals, button1)==0) Blink(2);
  if (bitRead(vals, button2)==0) Blink(3);
}

void Blink(byte n)
{
  for (byte i = 0; i < n; i++) {
    sbi(PORTB, PB5);  // turn the LED on (HIGH is the voltage level)
    delay(300);
    cbi(PORTB, PB5);  // turn the LED off by making the voltage LOW
    delay(200);
  }
}
