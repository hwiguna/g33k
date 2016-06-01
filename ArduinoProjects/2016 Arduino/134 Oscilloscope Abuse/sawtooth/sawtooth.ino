void setup() {
  DDRD = B11111111; // Set all bits of PORTD as output
}

void loop() {
  for (uint8_t y=0; y<=255; y++) // Loop through all possible y values of a byte
  {
    // Only "plot" when y is divisible by 25
    if ((y%25)==0)
        PORTD = y;
    delayMicroseconds(50); // Let it linger
  }
}
