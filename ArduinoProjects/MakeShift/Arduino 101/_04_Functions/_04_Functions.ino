int led0 = 4;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 4..11 as an output.
  for (int i = 0; i < 8; i++)
    pinMode(led0 + i, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  UpwardSequence();
  DownwardSequence();
}

void UpwardSequence()
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(led0 + i, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(100);                   // wait for a tenth of second
    digitalWrite(led0 + i, LOW);  // turn the LED off by making the voltage LOW
  }
}

void DownwardSequence()
{
  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(led0 + i, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(100);                   // wait for a tenth of second
    digitalWrite(led0 + i, LOW);  // turn the LED off by making the voltage LOW
  }
}

