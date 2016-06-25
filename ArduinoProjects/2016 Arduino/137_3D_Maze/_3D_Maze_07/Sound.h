byte tonePin = 2; // Which digital pin the beeper is attached to
void Beep()
{
  tone(2, 523, 62); // NOTE_C5, 1000/16
}
