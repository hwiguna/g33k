// v01 - Blink using direct port manipulation
// v01 - read button using direct port manipulation

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

void setup() {
  sbi(DDRC, PC0); // Pin D13 (PB5) as output
  cbi(DDRD, PD4); // D2 (PD2) as input
  PORTD |= B00010000;
}

// the loop function runs over and over again forever
void loop() {
  if (bitRead(PIND, PD4))
    sbi(PORTC,PC0);   // turn the LED on (HIGH is the voltage level)
  else
    cbi(PORTC,PC0);   // turn the LED off by making the voltage LOW
}
