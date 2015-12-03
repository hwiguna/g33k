int led0 = 4;
int button0 = 2;
bool gameOver = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 4..11 as an output.
  for (int i = 0; i < 8; i++)
    pinMode(led0 + i, OUTPUT);

  pinMode(button0, INPUT_PULLUP);
  pinMode(button0 + 1, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
    UpwardSequence(); // Right to left
    WaitForButton(1); // Wait for left button
    DownwardSequence(); // Left to right
    WaitForButton(0); // Wait for right button
}

void WaitForButton(int player)
{
  if (gameOver) return;
  
  bool gotIt = false;
  unsigned long timesUp = millis() + 1000;
  while (millis() < timesUp && !gotIt) {
    if (digitalRead(button0 + player) == LOW)
      gotIt = true;
  }
  if (!gotIt) GameOver(player);
}

void GameOver(int player)
{
  gameOver = true;
  
  if (player == 0) // player 0 lost
  {
    // Indicate that player 0 Lost
    digitalWrite(led0, HIGH);
  }
  else
  {
    // Indicate that player 1 lost
    digitalWrite(led0+7, HIGH);
  }
}

void UpwardSequence()
{
  if (gameOver) return;
  
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(led0 + i, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(100);                   // wait for a tenth of second
    digitalWrite(led0 + i, LOW);  // turn the LED off by making the voltage LOW
  }
}

void DownwardSequence()
{
  if (gameOver) return;

  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(led0 + i, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(100);                   // wait for a tenth of second
    digitalWrite(led0 + i, LOW);  // turn the LED off by making the voltage LOW
  }
}

