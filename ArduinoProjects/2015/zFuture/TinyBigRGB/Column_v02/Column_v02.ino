// ATTiny84 8x8 Matrix - GREEN columns
// by Hari Wiguna, 2015

// v2 - Adding SPI master to control second ATTiny

//=== SPI ===
#include <tinySPI.h>               //http://github.com/JChristensen/tinySPI

//== Column variables ==
const int ON = LOW;
const int OFF = HIGH;
int dly = 60;
int colPins[8] = {10, 9, 8, 7, 3, 2, 1, 0};

void setup() {
  //-- SPI --
  //pinMode (slaveSelectPin, OUTPUT); // set the slaveSelectPin as an output
  SPI.begin(); // initialize SPI

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
    SetRow(r,1);
    for (int c = 0; c < 8; c++)
    {
      digitalWrite(colPins[c], ON);
      delay(dly);
      digitalWrite(colPins[c], OFF);
    }
    SetRow(r,0);
  }
}

void SetRow(int row, int state)
{
  //digitalWrite(slaveSelectPin, LOW); // LOW = Hey, SPI slave, PAY ATTENTION to me, your master!
  SPI.transfer('0'+row);
  SPI.transfer('0'+state);
  SPI.transfer('\n');
  //digitalWrite(slaveSelectPin, HIGH); // HIGH= You can ignore me now, I'm going to talk to other slaves!
}

