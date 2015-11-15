byte pinStart = 2;

void setup() {
  for (byte i = 0; i < 4; i++) {
    pinMode(pinStart + i, OUTPUT);
    digitalWrite(pinStart + i, HIGH);
  }
}

void loop() {
  for (byte i = 0; i < 4; i++) {
    // Leave pin i HIGH while bringing other pins LOW one at a time
    for (byte j = 0; i < 4; i++) {
      if (i != j) {
        digitalWrite(pinStart + i, LOW);
        delay(500);
        digitalWrite(pinStart + i, HIGH);
      }
    }
  }
}
