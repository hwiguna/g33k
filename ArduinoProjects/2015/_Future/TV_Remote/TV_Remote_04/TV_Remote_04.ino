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

volatile bool hit = false;
volatile bool buttonState[10]; // 1=Pressed

void setup() {
  cli(); // turn off interrupt while we setup interrupts

  sbi(DDRB, PB5); // Pin D13 (PB5) as output
  sbi(DDRB, PB4); // Pin D12 (PB4) as output

  // Set D2..D11 aka PD2..PD7, PB0..PB3 to input
  for (byte i = 0; i < 10; i++) {
    pinMode(2 + i, INPUT);
    digitalWrite(2 + i, HIGH); // Enable pullup resistor
  }
  ClearButtonStates();

  // Listen to interrupts: PCINT0..PCINT3 (on D8..D11)
  PCMSK0 = _BV(PCINT0) + _BV(PCINT1) + _BV(PCINT2) + _BV(PCINT3);
  // Listen to interrupts: PCINT18..23 (on D2..D7)
  PCMSK2 = 0xFF - _BV(PCINT16) - _BV(PCINT17); // All bits HIGH except lowest 2 bits (used by RX & TX)

  sbi(PCICR, PCIE0);
  sbi(PCICR, PCIE2); // enable pin change interrupt: PCIE0=PCINT7..0|PCMSK0, PCIE1=PCINT14..8|PCMSK1, PCIE2=PCINT23..16|PCMSK2

  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

void loop() {
  if (hit)
  {
    for (byte i = 0; i < 10; i++)
    {
      if (buttonState[i])
      {
        ClearButtonStates();
        Blink(1+i);
        break;
      }
    }

    hit = false;
  }
}

void ClearButtonStates()
{
  for (byte i = 0; i < 10; i++)
  {
    buttonState[i] = false;
  }
}

// enabled interrupt X fires ISR(Interrupt Service Routine) Y: PCIE0>PCINT0_vect, PCIE1>PCINT1_vect, PCIE2>PCINT2_vect
ISR(PCINT0_vect) {
  cli(); // turn off interrupt to avoid switch noise
  delay(1); // wait till switch settles
  bool any = false;
  for (byte i = 0; i < 4; i++)
  {
    buttonState[6 + i] = (PINB & _BV(i)) == 0; // If bit is low, that button is pressed
    any = true;
  }
  hit = any;
    sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

ISR(PCINT2_vect) {
  cli(); // turn off interrupt to avoid switch noise
  delay(1); // wait till switch settles
  bool any = false;
  for (byte i = 0; i < 6; i++)
  {
    buttonState[i] = (PIND & _BV(2 + i)) == 0; // If bit is low, that button is pressed
    any = true;
  }
  hit = any;
    sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

void Blink(byte n)
{
  for (byte i = 0; i < n; i++) {
    delay(250);
    sbi(PORTB, PB5);  // turn the LED on (HIGH is the voltage level)
    delay(200);
    cbi(PORTB, PB5);  // turn the LED off by making the voltage LOW

  }
}
