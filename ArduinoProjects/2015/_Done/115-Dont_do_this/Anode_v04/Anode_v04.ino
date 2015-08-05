// ATTiny84 8x8 Matrix - ANODE Rows

// v2 - Adding *SPI SLAVE* to listen for signal to switch row
// v3 - Unable to get slave SPI and I2C, now just using PA7 pin to trigger the row change
//      That sorta work, but too slow
// v4 - Using Pin Change Interrupt, works great. Still has shadowing.

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//=== Row Variables ==
int anodePins[8] = {0, 1, 2, 3, 7, 8, 9, 10};
const int ON = HIGH;
const int OFF = LOW;
const int rowSyncPin = 6; // PA6 (ATTiny84 pin 7) Blue
int rowIncrementPin = 5; // PA5 (ATTiny84 pin 8) White
volatile int r = 0;
int prevR = 7;

void setup() {
  pinMode(rowSyncPin, INPUT);
  pinMode(rowIncrementPin, INPUT);

  sbi(GIMSK, PCIE0); // Turn on Pin Change interrupt
  sbi(PCMSK0, PCINT5); // Which pins are affected by the interrupt
  sbi(PCMSK0, PCINT6); // Which pins are affected by the interrupt

  //-- Row pins init --
  for (int i = 0; i < 8; i++)
  {
    pinMode(anodePins[i], OUTPUT);
    digitalWrite(anodePins[i], OFF);
  }
}

ISR(PCINT0_vect) {
  if (PINA & B01000000) {
    r = 0; }
  else if (PINA & B00100000)
    r++;
}

void loop() {
  //  if (bit_is_set(PORTA, PINA5))
  //    digitalWrite(anodePins[1], OFF);
  //  else
  //    digitalWrite(anodePins[1], ON);

  if (r != prevR)
  {
    digitalWrite(anodePins[prevR], OFF);
    digitalWrite(anodePins[r], ON);
    prevR = r;
  }
}
