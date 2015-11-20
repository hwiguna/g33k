// RGB Spire Tester
// Hari Wiguna 2015
// v1 - test all levels, not worrying about color sequence
// v2 - make sure that colors are tested in same sequence for all levels

byte pinStart = 2; // Connect spire to D2, d3, D4, D5

void setup() {
  for (byte i = 0; i < 4; i++) {
    pinMode(pinStart + i, INPUT);
  }
}

void loop() {
  for (int i = 3; i >= 0; i--) {
    byte gnd = pinStart + i;
    pinMode(gnd, OUTPUT);
    digitalWrite(gnd, HIGH);

    for (byte j = 2; j < 3; j++) {
      byte c = i + 1 + j;
      if (c > 3) c = c - 4;
      Flash(pinStart + c);
      delay(50);
    }

    digitalWrite(gnd, LOW);
    pinMode(gnd, INPUT);
  }
  //delay(20);
}

void Flash(byte pin)
{
  for (int f = 0; f < 10; f++)
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(1);

    digitalWrite(pin, HIGH);
    pinMode(pin, INPUT);
    delay(15);
  }
}

