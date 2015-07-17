// ATTiny84 8x8 Matrix - ANODE Rows

// v2 - Adding *SPI SLAVE* to listen for signal to switch row
// v3 - Unable to get slave SPI and I2C, now just using PA7 pin to trigger the row change

//=== Row Variables ==
int anodePins[8] = {0, 1, 2, 3, 7, 8, 9, 10};
const int ON = HIGH;
const int OFF = LOW;
const int rowSyncPin = 6; // PA6 (ATTiny84 pin 7) Blue
int rowIncrementPin = 5; // PA5 (ATTiny84 pin 8) White
int r = 0;
int prevR = 7;

void setup() {
  pinMode(rowSyncPin, INPUT);
  pinMode(rowIncrementPin, INPUT);

  //-- Row pins init --
  for (int i = 0; i < 8; i++)
  {
    pinMode(anodePins[i], OUTPUT);
    digitalWrite(anodePins[i], OFF);
  }
}

void loop() {
  if (digitalRead(rowIncrementPin) == HIGH)
  {
    if (digitalRead(rowSyncPin) == HIGH)
      r = 0;

    digitalWrite(anodePins[prevR], OFF);
    digitalWrite(anodePins[r], ON);
    prevR = r;
    if (r < 8) r++;
  }
}
