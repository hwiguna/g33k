// Arduino Magic Trick
// by Hari Wiguna, 2015

const int ON = LOW;
const int OFF = HIGH;

int dly = 40;

int rowPins[8] = {0, 1, 2, 3, 7, 8, 9, 10};
int colPins[8] = {10, 9, 8, 7, 3, 2, 1, 0};

void setup() {
  for (int i = 0; i < 8; i++)
  {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], OFF);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], OFF);
  }
}

void loop() {
  for (int r = 0; r < 8; r++)
  {
    for (int c=0; c<8; c++)
    {
      digitalWrite(colPins[c], ON);
      delay(dly);
      digitalWrite(colPins[c], OFF);
    }
  }
}
