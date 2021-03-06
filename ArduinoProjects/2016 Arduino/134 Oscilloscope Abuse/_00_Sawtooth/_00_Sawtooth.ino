// Sawtooth on scope by Hari Wiguna, 2016
// Playing with R-2R Ladder to convert Digital to Analog
// We'll use PORTD because it gives us contiguous 8 bits
// To see this code in action, search for HariFun#134 on YouTube.

void setup() {
  DDRD = B11111111; // Set all bits of PORTD as output
}

void loop() {
  for (uint8_t y=0; y<=255; y++) // Loop through all possible y values of a byte
  {
    PORTD = y; // Slap the bits to Arduino pins D0..D7
    delayMicroseconds(50); // Let it linger
  }
}
