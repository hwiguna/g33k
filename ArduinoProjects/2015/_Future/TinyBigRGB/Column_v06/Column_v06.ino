// ATTiny84 8x8 Matrix - GREEN columns
// by Hari Wiguna, 2015

// v2 - Adding *SPI MASTER* to tell second ATTiny to switch row
// v3 - Unable to get slave SPI and I2C, now just using PA7 pin to trigger the row change
// v4 - Clear ports so when we switch row, we start with all columns off
// v5 - no change to row sketch, only the column is animated
// v6 - rewire the IO pins so all LED pins are on PORTA and comm on PORTB

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//== Column variables ==
const int ON = LOW;
const int OFF = HIGH;
const int rowIncrementPin = PB0; // (ATTiny84 pin 2) Yellow
const int rowSyncPin = PB1; // (ATTiny84 pin 3) White
char rowPattern[][8] = {
  {
    B11111111,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B11111111,
  }, {
    B00000001,
    B00000011,
    B00000111,
    B00001111,
    B00011111,
    B00111111,
    B01111111,
    B11111111,
  },
  //  {
  //    B11111111,
  //    B11111110,
  //    B11111100,
  //    B11111000,
  //    B11110000,
  //    B11100000,
  //    B11000000,
  //    B10000000,
  //  },

  //  {
  //    B11000011,
  //    B00100100,
  //    B01111110,
  //    B11011011,
  //    B11011011,
  //    B01111110,
  //    B00111100,
  //    B00000000 // First frame for alien #2
  //  },
  //  {
  //    B00100100,
  //    B00100100,
  //    B00100100,
  //    B01111110,
  //    B11011011,
  //    B11011011,
  //    B01111110,
  //    B00111100 // Second frame for alien #2
  //  }
};

int dly = 500;
int p = 0;
long nextFrame = 0;

void setup() {
  DDRB = B00000011; // PB0..PB1 are set to outputs
  PORTB = 0;

  //-- Init column pins --
  DDRA = 0xFF; // PA0..PA7 are outputs;
  PORTA = 0xFF; // for columns 1 = off
}

void loop() {

  for (int r = 0; r < 8; r++)
  {
    //10, 9, 8, 7, 3, 2, 1, 0
    //PORTA = B10001111;
    //PORTB = B00000111;
    //PORTA = 0xFF;

    //-- This first blip will turn off the row --
    digitalWrite(10, HIGH);
    digitalWrite(10, LOW);

    //-- Then we put the new row pattern --
    PORTA = ~rowPattern[p][r];

    //-- Finally, we turn on the NEW row --
    if (r == 0)
    {
      digitalWrite(9, HIGH);
      digitalWrite(9, LOW);
    }
    else
    {
      digitalWrite(10, HIGH);
      digitalWrite(10, LOW);
    }

//-- Let slow humans enjoy the one row of LED pattern --
    delayMicroseconds(dly);
  }

  if (millis() >= nextFrame)
  {
    p++;
    if (p >= 2) p = 0;
    nextFrame = millis() + 1000;
  }
}


