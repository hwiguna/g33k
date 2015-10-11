int baseLed = 10;   // 10,11,12,13
int baseButton = 6; // 6,7,8,9
const int maxLen = 5;
int waitTime = 1000;
bool isGameOver = false;

int sequence[maxLen];
int len = 0;

void setup() {
  for (int i = 0; i < 4; i++)
  {
    pinMode(baseLed + i, OUTPUT);

    pinMode(baseButton + i, INPUT);
    digitalWrite(baseButton + i, HIGH);
  }
}

// the loop function runs over and over again forever
void loop() {
  if (!isGameOver)
  {
    SimonSays();
    YouSay();
  }
}

void SimonSays()
{
  // Generate next random sequence
  sequence[len] = random(0, 4);

  // playback sequence so far
  for (int i = 0; i < len; i++)
  {
    digitalWrite(baseLed + sequence[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);
    digitalWrite(baseLed + sequence[i], LOW);   // turn the LED on (HIGH is the voltage level)
    delay(500);
  }
}

void YouSay()
{
  int yourLen = 0;
  int timesUp = millis() + waitTime;

  // Wait for button press...
  while (millis() < timesUp)
  {
    int current = sequence[yourLen];
    if (digitalRead(baseButton + current) == LOW) {
      FlashLed(current);
      yourLen++;
      if (yourLen < len)
        timesUp = millis() + waitTime;
    }
  }

  if (yourLen < len)
    YouLoose();
}

void FlashLed(int whichButton)
{
  digitalWrite(baseLed + whichButton, HIGH);
  delay(500);
  digitalWrite(baseLed + whichButton, LOW);
}

void All(int state)
{
  for (int i = 0; i < 4; i++)
    digitalWrite(baseLed + i, state);
}

void YouWin()
{
  for (int i = 0; i < 10; i++)
  {
    All(HIGH);
    delay(100);
    All(LOW);
    delay(100);
  }
  
  isGameOver = true;
}

void YouLoose()
{
  for (int i = 0; i < 3; i++)
  {
    All(HIGH);
    delay(2000);
    All(LOW);
    delay(1000);
  }
  
  isGameOver = true;
}

