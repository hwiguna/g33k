// ATTiny84 8x8 Matrix - ANODE Rows

// v2 - Adding *SPI SLAVE* to listen for signal to switch row
// v3 - Unable to get slave SPI and I2C, now just using PA7 pin to trigger the row change
//      That sorta work, but too slow
// v4 - Using Pin Change Interrupt, works great. Still has shadowing.
// v5 - no change to row sketch, only the column is animated
// v6 - rewire the IO pins so all LED pins are on PORTA and comm on PORTB

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
volatile int r = 1;
int prevR = 7;

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
  byte pinB = PINB;
  
  if (pinB & B00000010) {
    cbi(PORTA,7);
    r = 0;
    sbi(PORTA,r);}
  else if (pinB & B00000001) {
    cbi(PORTA,r);
    r++;
    sbi(PORTA,r);
  }
}

void loop() {
  if (r != prevR)
  {
//    cbi(PORTA,prevR);
//    sbi(PORTA,r);
//digitalWrite(prevR,LOW);
//digitalWrite(r,HIGH);
    prevR = r;
  }
}
