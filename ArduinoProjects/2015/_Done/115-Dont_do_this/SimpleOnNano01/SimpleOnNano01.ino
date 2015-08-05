//
// v00 - Simple loop through all 64 LEDs
// v01 - Draw bitmap

char rowPattern[][8] = {
  {
    B00000000, // First frame for alien #2
    B00111100,
    B01111110,
    B11011011,
    B11011011,
    B01111110,
    B00100100,
    B11000011,
  },
  {
    B00111100, // Second frame for alien #2
    B01111110,
    B11011011,
    B11011011,
    B01111110,
    B00100100,
    B00100100,
    B00100100,
  }
};

int p = 0;
long timeToAnimate;

void setup() {
  for (byte i = 0; i < 8; i++) {
    pinMode(0 + i, OUTPUT);
    pinMode(8 + i, OUTPUT);
  }
}

void loop() {
  for (byte r = 0; r < 8; r++)
  {
    for (byte c = 0; c < 8; c++)
    {
      digitalWrite(0 + c, 1 - bitRead(rowPattern[p][r], c));
    }
    digitalWrite(8 + r, HIGH);
    delayMicroseconds(100);
    digitalWrite(8 + r, LOW);
  }
  if (millis() > timeToAnimate)
  {
    p++;
    if (p > 1) p = 0;
    timeToAnimate = millis() + 500;
  }
}
