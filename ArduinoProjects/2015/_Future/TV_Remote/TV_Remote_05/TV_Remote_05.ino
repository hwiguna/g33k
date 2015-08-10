// v01 - Blink using direct port manipulation
// v02 - read button using direct port manipulation
// v03 - Blink n times based on which button is pressed
// v04 - Read buttons using interrupt instead of polling in loop()
// v05 - Sleep!

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
  cbi(DDRD, button1);
  cbi(DDRD, button2);

set_sleep_mode(<mode>);
  cli(); // turn off interrupt while we setup interrupts
  sbi(PCICR, PCIE2); // enable pin change interrupt: PCIE0=PCINT7..0|PCMSK0, PCIE1=PCINT14..8|PCMSK1, PCIE2=PCINT23..16|PCMSK2
  //sbi(PCMSK2, PCINT19); // choose which pin(s) should fire the above pin change interrupt on PD2 / D02
  PCMSK2 = _BV(PCINT20) + _BV(PCINT19) + _BV(PCINT18); // 18=D2, 19=D3, 20=D4
  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

void loop() {
  delay(1000);
  cbi(PORTB, PB5);  // turn the LED off by making the voltage LOW
}

// enabled interrupt X fires ISR(Interrupt Service Routine) Y: PCIE0>PCINT0_vect, PCIE1>PCINT1_vect, PCIE2>PCINT2_vect
ISR(PCINT2_vect) {
  sbi(PORTB, PB5);  // turn the LED on (HIGH is the voltage level)
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
