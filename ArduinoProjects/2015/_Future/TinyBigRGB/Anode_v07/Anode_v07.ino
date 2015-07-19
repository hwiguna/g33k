// ATTiny84 8x8 Matrix - ANODE Rows

// v2 - Adding *SPI SLAVE* to listen for signal to switch row
// v3 - Unable to get slave SPI and I2C, now just using PA7 pin to trigger the row change
//      That sorta work, but too slow
// v4 - Using Pin Change Interrupt, works great. Still has shadowing.
// v5 - no change to row sketch, only the column is animated
// v6 - rewire the IO pins so all LED pins are on PORTA and comm on PORTB
// v7 - send row change twice: 1. turn off row and increment, 2. turn on row.

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//=== Row Variables ==
const int ON = HIGH;
const int OFF = LOW;
const int rowIncrementPin = PB0; // (ATTiny84 pin 2) Yellow
const int rowSyncPin = PB1; // (ATTiny84 pin 3) White
volatile int row = 1;

void setup() {
  DDRB = B00000000; // PB0..PB7 are set to inputs

  sbi(GIMSK, PCIE1); // Turn on Pin Change interrupt
  sbi(PCMSK1, PCINT8); // Which pins are affected by the interrupt
  sbi(PCMSK1, PCINT9); // Which pins are affected by the interrupt

  //-- Row pins init --
  DDRA = 0xFF; // PA0..PA7 are outputs;
  PORTA = 0x00; // All off
}

ISR(PCINT1_vect) {
  //-- Sync Row --
  if (PINB & B00000010) {
    row = 0;
    PORTA = _BV(7 - row); // 7-row to invert the image because matrix is upside-down on the breadboard
  }
  else
    //-- Increment Row --
    if (PINB & B00000001) {
      row++;
      if (row <= 7)
        PORTA = _BV(7 - row);
    }
}

void loop() {
  // All work is done by interrupt
}

