// v01 - Blink using direct port manipulation

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

void setup() {
  sbi(DDRB, 5);  // Pin D13 as output
}

// the loop function runs over and over again forever
void loop() {
  sbi(PORTB,5);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  cbi(PORTB,5);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
