// ATTiny84 8x8 Matrix - GREEN columns
// by Hari Wiguna, 2015

// v2 - Adding *SPI MASTER* to tell second ATTiny to switch row
// v3 - Unable to get slave SPI and I2C, now just using PA7 pin to trigger the row change
// v4 - Clear ports so when we switch row, we start with all columns off
// v5 - no change to row sketch, only the column is animated

//== Column variables ==
const int ON = LOW;
const int OFF = HIGH;
int colPins[8] = {10, 9, 8, 7,  3, 2, 1, 0};
int rowSyncPin = 6; // PA6 (ATTiny84 pin 7) Blue
int rowIncrementPin = 5; // PA5 (ATTiny84 pin 8) White
char rowPattern[][8] = {
  //  {
  //    B11111111,
  //    B10000001,
  //    B10000001,
  //    B10000001,
  //    B10000001,
  //    B10000001,
  //    B10000001,
  //    B11111111,
  //  }, {
  //    B00000001,
  //    B00000011,
  //    B00000111,
  //    B00001111,
  //    B00011111,
  //    B00111111,
  //    B01111111,
  //    B11111111,
  //  },
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

  {
    B11000011,
    B00100100,
    B01111110,
    B11011011,
    B11011011,
    B01111110,
    B00111100,
    B00000000 // First frame for alien #2
  },
  {
    B00100100,
    B00100100,
    B00100100,
    B01111110,
    B11011011,
    B11011011,
    B01111110,
    B00111100 // Second frame for alien #2
  }
};

int dly = 500;
int p = 0;
long nextFrame = 0;

void setup() {
  pinMode(rowSyncPin, OUTPUT);
  pinMode(rowIncrementPin, OUTPUT);

  //-- Init column pins --
  for (int i = 0; i < 8; i++)
  {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], OFF);
  }
}

void loop() {

  for (int r = 0; r < 8; r++)
  {
    //10, 9, 8, 7, 3, 2, 1, 0
    PORTA = B10001111;
    PORTB = B00000111;

    if (r == 0)
    {
      digitalWrite(rowSyncPin, HIGH);
      digitalWrite(rowSyncPin, LOW);
    }
    else
    {
      digitalWrite(rowIncrementPin, HIGH);
      digitalWrite(rowIncrementPin, LOW);
    }

    //TODO: change this to PORTA command
    for (int c = 0; c < 8; c++) {
      digitalWrite(colPins[c], 1 - bitRead( rowPattern[p][r], c));
    }
    delayMicroseconds(dly);
  }

  if (millis() >= nextFrame)
  {
    p++; 
    if (p >= 2) p = 0;
    nextFrame = millis() + 1000;
  }
} 


