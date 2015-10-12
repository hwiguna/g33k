// Simon Says
// Hari Wiguna 2015
// Arduino 101 @ MakeShift Lincoln

//-- Simon's sequence --
const int maxLen = 5; // How long is the winning sequence?
int sequence[maxLen];

//-- Difficulty Level --
int waitTime = 1000; // in miliseconds, larger# means easier :-)

//-- Wiring --
int led0 = 6;   // 6,7,8,9
int button0 = 2; // 2,3,4,5

//-- Other Variables --
bool isGameOver = false;
int len = 0; // Current length of Simon's sequence.

//=== This code runs once ===
void setup() {
  Serial.begin(9600); // Only needed for debugging.

  //-- Initialize ports --
  for (int i = 0; i < 4; i++)
  {
    pinMode(led0 + i, OUTPUT); // Set LED pins to OUTPUT.

    pinMode(button0 + i, INPUT); // Set Button pins to INPUT.
    digitalWrite(button0 + i, HIGH); // Enable internal pullup resistor so buttons are HIGH when not pressed.
  }

  randomSeed(analogRead(0));
}

//=== the loop function runs over and over again forever ===
void loop() {
  SimonSays();
  PlayerSays();
  delay(1000);
}

void SimonSays()
{
  if (isGameOver)
    return;

  // Generate next random sequence
  sequence[len] = random(0, 4);
  len++;

  Serial.print("SIMON SAYS LEN=");
  Serial.print(len);
  Serial.print(": ");

  // playback sequence so far
  for (int i = 0; i < len; i++)
  {
    Serial.print(sequence[i]);
    Serial.print(", ");
    digitalWrite(led0 + sequence[i], HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(250);
    digitalWrite(led0 + sequence[i], LOW);   // turn the LED on (HIGH is the voltage level)
    delay(500);
  }
  Serial.println();
}

void PlayerSays()
{
  if (isGameOver)
    return;

  Serial.print("PLAYER SAYS LEN=");
  Serial.println(len);

  //-- Loop until player has repeated all Simon's sequence --
  int yourLen = 0;
  while (yourLen < len)
  {
    bool isCorrect = false; // Assume player will fail
    unsigned long timesUp = millis() + waitTime; // When do we decide that we've waited long enough for player?

    int current = sequence[yourLen];
    Serial.print("Waiting for ");
    Serial.print(current);

    Serial.print("  timesUp=");
    Serial.print(timesUp);

    //-- Wait for the correct button to be pressed --
    while (millis() < timesUp && !isCorrect) // get out when time is up or player pressed to the correct button.
    {
      if (digitalRead(button0 + current) == LOW) {
        Serial.print(" Pressed. ");
        isCorrect = true;
        FlashLed(current);
      }
    }

    if (isCorrect) {
      // If player pressed the correct button in time, advance to the next sequence
      yourLen++;
      Serial.print(" Next... yourLen=");
      Serial.println(yourLen);
    }
    else {
      // If player missed the correct button, GAME OVER!
      Serial.print(" YOU MISSED!  GAME OVER!");
      Serial.println(millis());
      YouLoose();
      len = 0; // force out of while loop
    }
  }

  // if we got this far and len has reached maxLen, then player has repeated the max Simon Sequence, player wins!
  if (len == maxLen)
    YouWin();
}

void FlashLed(int whichLed)
{
  digitalWrite(led0 + whichLed, HIGH);
  delay(250);
  digitalWrite(led0 + whichLed, LOW);
}

void All(int state)
{
  for (int i = 0; i < 4; i++)
    digitalWrite(led0 + i, state);
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
  All(HIGH);
  for (int i = 0; i < 4; i++)
    FlashLed(3 - i);
  isGameOver = true;
}

