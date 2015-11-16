// RGB Spire Tester
// Hari Wiguna 2015
// v1 - test all levels, not worrying about color sequence

byte pinStart = 2; // Connect spire to D2, d3, D4, D5

void setup() {
  for (byte i = 0; i < 4; i++) {
    pinMode(pinStart + i, INPUT);
  }
}

void loop() {
  for (byte i = 0; i < 4; i++) {
    
    pinMode(pinStart + i, OUTPUT);
    digitalWrite(pinStart + i, HIGH);
    
    for (byte j = 0; j < 4; j++) {
      if (i != j) {
        pinMode(pinStart + j, OUTPUT);
        Flash(pinStart + j);
        pinMode(pinStart + j, INPUT);
        delay(1000);
      }
    }

    digitalWrite(pinStart + i, LOW);
    pinMode(pinStart + i, INPUT);
  }
  //delay(20);
}

void Flash(byte pin)
{
  for (int f = 0; f < 10; f++)
  {
    digitalWrite(pin, LOW);
    delay(1);
    digitalWrite(pin, HIGH);

    delay(15);
  }
}

