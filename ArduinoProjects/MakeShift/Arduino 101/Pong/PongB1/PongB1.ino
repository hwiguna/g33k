int btnLeft = 3;
int btnRight = 2;
int led0 = 4;

int PRESSED = 0;

int ballDirection = 0;

void setup() {
  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);

  for (int x = 0; x < 8; x++)
  {
    pinMode(led0 + x, OUTPUT);
  }
}

void loop() {
  //-- wait for start --
  while (ballDirection == 0)
  {
    if (digitalRead(btnLeft) == PRESSED) ballDirection = +1;
    if (digitalRead(btnRight) == PRESSED) ballDirection = -1;
  }

  //-- Playing the game --
  if (ballDirection == 1)
  {
    TurnAllOff();
    MoveBallLeftToRight();
    WaitForRightPlayer();
  }

  if (ballDirection == -1)
  {
    TurnAllOff();
    MoveBallRightToLeft();
    WaitForLeftPlayer();
  }
}

void WaitForRightPlayer()
{
  ballDirection = 0;
  unsigned long timeout = millis() + 1000L;
  while (millis() < timeout)
  {
    if (digitalRead(btnRight) == PRESSED) {
      ballDirection = -1;
      exit;
    }
  }
  if (ballDirection==0) RightPlayerLoses();
}

void WaitForLeftPlayer()
{
  ballDirection = 0;
  unsigned long timeout = millis() + 1000L;
  while ((millis() < timeout))
  {
    if (digitalRead(btnLeft) == PRESSED)  {
      ballDirection = +1;
      exit;
    }
  }
  if (ballDirection==0) LeftPlayerLoses();
}

void MoveBallRightToLeft()
{
  for (int x = 0; x < 8; x++)
  {
    digitalWrite(led0 + x, HIGH);
    delay(500);
    digitalWrite(led0 + x, LOW);
  }
}

void MoveBallLeftToRight()
{
  for (int x = 7; x >= 0; x--)
  {
    digitalWrite(led0 + x, HIGH);
    delay(500);
    digitalWrite(led0 + x, LOW);
  }
}

void RightPlayerLoses()
{for (int x = 0; x < 3; x++)
  {
    digitalWrite(led0, LOW);
    delay(100);
    digitalWrite(led0, HIGH);
    delay(100);
  }
}


void LeftPlayerLoses()
{for (int x = 0; x < 3; x++)
  {
    digitalWrite(led0 + 7, LOW);
    delay(100);
    digitalWrite(led0+7, HIGH);
    delay(100);
  }
}

void TurnAllOff()
{
  for (int x = 0; x < 8; x++)
  {
    digitalWrite(led0 + x, LOW);
  }
}

