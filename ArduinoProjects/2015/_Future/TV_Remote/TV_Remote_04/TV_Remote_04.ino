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
const byte button3 = PD5;
volatile bool hit = false;

void setup() {
  // Set D2..D12 aka PD2..PD7, PB0..PB4 to input
  for (byte i=2;i<13;i++) {
    pinMode(i,INPUT);
    digitalWrite(i,HIGH); // Enable pullup resistor
  }

  sbi(DDRB, PB5); // Pin D13 (PB5) as output

  cli(); // turn off interrupt while we setup interrupts

  sbi(PCICR, PCIE0);
  sbi(PCICR, PCIE2); // enable pin change interrupt: PCIE0=PCINT7..0|PCMSK0, PCIE1=PCINT14..8|PCMSK1, PCIE2=PCINT23..16|PCMSK2
  
  // Listen to interrupts: PCINT0..PCINT4 (on D8..D12)
  PCMSK0 = _BV(PCINT0) + _BV(PCINT1) + _BV(PCINT2) + _BV(PCINT3) + _BV(PCINT4);
  // Listen to interrupts: PCINT18..23 (on D2..D7)
  PCMSK2 = 0xFF - _BV(PCINT16) - _BV(PCINT17); // All except lowest 2 bits
  
  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

void loop() {
  if (hit) Blink(1);
}

// enabled interrupt X fires ISR(Interrupt Service Routine) Y: PCIE0>PCINT0_vect, PCIE1>PCINT1_vect, PCIE2>PCINT2_vect
ISR(PCINT0_vect) {
  InterruptHandler();
}
ISR(PCINT2_vect) {
  InterruptHandler();
}

void InterruptHandler()
{
  hit = true;
  cli(); // turn off interrupt to avoid switch noise
}

void Blink(byte n)
{
  hit = false;
  for (byte i = 0; i < n; i++) {
    sbi(PORTB, PB5);  // turn the LED on (HIGH is the voltage level)
    delay(300);
    cbi(PORTB, PB5);  // turn the LED off by making the voltage LOW
    delay(200);
  }
  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}
