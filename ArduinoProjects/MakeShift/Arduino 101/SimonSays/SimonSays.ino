int baseLed = 10;   // 10,11,12,13
int baseButton = 6; // 6,7,8,9
const int maxLen = 5;
unsigned long waitTime = 1000L;
bool isGameOver = false;

int sequence[maxLen];
int len = 0;


void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++)
  {
    pinMode(baseLed + i, OUTPUT);

    pinMode(baseButton + i, INPUT);
    digitalWrite(baseButton + i, HIGH);
  }

  int x = random(0, 4);
}

// the loop function runs over and over again forever
void loop() {
  SimonSays();
  YouSay();
  delay(1000);
}

void SimonSays()
{
  if (isGameOver)
    return;


  // Generate next random sequence
  sequence[len] = random(0, 4);

  len++;
  if (len == maxLen)
    YouWin();

  Serial.print("SIMON SAYS LEN=");
  Serial.print(len);
  Serial.print(": ");

  // playback sequence so far
  for (int i = 0; i < len; i++)
  {
    Serial.print(sequence[i]);
    Serial.print(", ");
    digitalWrite(baseLed + sequence[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);
    digitalWrite(baseLed + sequence[i], LOW);   // turn the LED on (HIGH is the voltage level)
    delay(500);
  }

  Serial.println();
}

void YouSay()
{
  if (isGameOver)
    return;

  int yourLen = 0;

  Serial.print("YOU SAY LEN=");
  Serial.println(len);
  while (yourLen < len)
  {
    unsigned long timesUp = millis() + waitTime;

    // Wait for button press...
    bool youPassed = false;

    int current = sequence[yourLen];
    Serial.print("Waiting for ");
    Serial.print(current);

    Serial.print("  timesUp=");
    Serial.print(timesUp);

    while (millis() < timesUp && !youPassed)
    {
      if (digitalRead(baseButton + current) == LOW) {
        Serial.print(" Pressed. ");
        youPassed = true;
        FlashLed(current);
      }
    }

    if (youPassed) {
      yourLen++;
      Serial.print(" Next... yourLen=");
      Serial.println(yourLen);
    }
    else {
      Serial.print(" YOU MISSED!");
      Serial.println(millis());
      YouLoose();
      len = 0; // force out of while loop
    }
  }
}

void FlashLed(int whichLed)
{
  digitalWrite(baseLed + whichLed, HIGH);
  delay(500);
  digitalWrite(baseLed + whichLed, LOW);
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
    All(LOW);
    delay(100);
    All(HIGH);
    delay(100);
  }

  isGameOver = true;
}

void YouLoose()
{
  //  for (int i = 0; i < 3; i++)
  //  {
  //    All(HIGH);
  //    delay(2000);
  //    All(LOW);
  //    delay(1000);
  //  }

  isGameOver = true;
}

