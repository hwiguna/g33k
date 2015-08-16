// v01 - Blink using direct port manipulation
// v01 - read button using direct port manipulation

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

void setup() {
  sbi(DDRB, PB5); // Pin D13 (PB5) as output
  cbi(DDRD, PD2); // D2 (PD2) as input
}

// the loop function runs over and over again forever
void loop() {
  if (bitRead(PIND, PD2))
    sbi(PORTB,PB5);   // turn the LED on (HIGH is the voltage level)
  else
    cbi(PORTB,PB5);   // turn the LED off by making the voltage LOW
}
