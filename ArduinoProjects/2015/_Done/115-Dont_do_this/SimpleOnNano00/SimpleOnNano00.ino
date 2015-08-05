//
// Simple loop through all 64 LEDs
//
void setup() {
  for (byte i = 0; i < 8; i++) {
    pinMode(0 + i, OUTPUT);
    pinMode(8 + i, OUTPUT);
  }
}

void loop() {
  for (byte r = 0; r < 8; r++)
  {
    digitalWrite(8 + r, HIGH);
    for (byte c = 0; c < 8; c++)
    {
      digitalWrite(0 + c, LOW);
      delay(50);
      digitalWrite(0 + c, HIGH);
    }
    digitalWrite(8 + r, LOW);
  }
}
