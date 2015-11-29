// RGB Spire Tester
// Hari Wiguna 2015
// v1 - test all levels, not worrying about color sequence
// v2 - make sure that colors are tested in same sequence for all levels
// v3 ?
// v4 - Use arrays to adjust to power rails wiring

byte pinArray[] = {4, 2, 3, 5}; // Connect spire to D2, d3, D4, D5

void setup() {
  for (byte i = 0; i < 4; i++) {
    pinMode(pinArray[i], INPUT);
  }
}

void loop() {
  //ColorTest();
  CylonTest();
}

void CylonTest()
{

  for (byte j = 0; j < 3; j++) {
    for (int i = 0; i < 4; i++) {
      byte gnd = pinArray[i];
      pinMode(gnd, OUTPUT);
      digitalWrite(gnd, HIGH);

      int c = i + j + 1; // 1=red, 2=green, 3=blue
      if (c > 3) c = c - 4;
      Flash(pinArray[c]);
      delay(10);

      digitalWrite(gnd, LOW);
      pinMode(gnd, INPUT);
    }

    for (int i = 2; i > 0; i--) {
      byte gnd = pinArray[i];
      pinMode(gnd, OUTPUT);
      digitalWrite(gnd, HIGH);

      int c = i + j + 1; // 1=red, 2=green, 3=blue
      if (c > 3) c = c - 4;
      Flash(pinArray[c]);
      delay(10);

      digitalWrite(gnd, LOW);
      pinMode(gnd, INPUT);
    }
  }
}



void ColorTest()
{
  for (int i = 0; i < 4; i++) {
    byte gnd = pinArray[i];
    pinMode(gnd, OUTPUT);
    digitalWrite(gnd, HIGH);

    for (byte j = 0; j < 3; j++) {
      int c = i + 1 + j;
      if (c > 3) c = c - 4;
      Flash(pinArray[c]);
      delay(500);
    }

    digitalWrite(gnd, LOW);
    pinMode(gnd, INPUT);
  }
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

