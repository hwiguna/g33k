// X-Pong by Hari Wiguna, 2015
// Original idea by Don Lamb

// Arduino Pins
int btnLeft = 13;
int btnRight = 4;
int led0 = 5;
int led7 = led0 + 7;

// Game variables
int ballPosition = 0;
int ballDirection = 0;
int prevBallPosition = 0;
int ballDelay = 100;
int debounceDelay = 200;

// Make code easier to read
int IsPressed = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);

  for (int x = 0; x <= 7; x++)
    pinMode(led0 + x, OUTPUT);
}

void loop() {
  if (ballDirection == 0)
    WaitForServe();
  else
  {
    DrawBall();
    DelayBall();
    if ((ballPosition == 0) && (ballDirection == -1)) WaitForPlayer(btnLeft, +1, 0);
    if ((ballPosition == 7) && (ballDirection == +1)) WaitForPlayer(btnRight, -1, 7);
    else {
      MoveBall();
    }
  }
}

void DelayBall()
{
  unsigned long timeout = millis() + ballDelay;
  while (millis() < timeout)
  {
    if ((ballPosition != 0 ) && (digitalRead(btnLeft) == IsPressed)) {
      GameOver(0);
      break;
    }

    if ((ballPosition != 7) && (digitalRead(btnRight) == IsPressed)) {
      GameOver(7);
      break;
    }
  }
}

void WaitForServe()
{
  while (true)
  {
    if (digitalRead(btnLeft) == IsPressed) {
      ballPosition = 0;
      ballDirection = +1;
      break;
    }
    if (digitalRead(btnRight) == IsPressed) {
      ballPosition = 7;
      ballDirection = -1;
      break;
    }
  }
  delay(200);
}

void SetLED(int which, int state)
{
  int pin = led7 - which;
  if (pin >= led0 && pin <= led7) digitalWrite(pin, state);
}

void GameOver(int which)
{
  for (int n = 0; n < 4; n++)
  {
    SetLED(which, HIGH);
    delay(100);
    SetLED(which, LOW);
    delay(100);
  }
  ballDirection = 0;
  ballDelay = 200;
}

void MoveBall()
{
  prevBallPosition = ballPosition;
  ballPosition = ballPosition + ballDirection;
}

void DrawBall()
{
  SetLED(prevBallPosition, LOW);
  SetLED(ballPosition, HIGH);
}

void WaitForPlayer(int buttonPin, int ballDir, int gameOverPin)
{
  ballDirection = 0;
  unsigned long timeout = millis() + 1000L;
  while (millis() < timeout)
  {
    if (digitalRead(buttonPin) == IsPressed) {
      delay(debounceDelay); // allow button to flutter
      ballDirection = ballDir;
      ballDelay =  ballDelay -  5;
      break;
    }
  }
  if (ballDirection == 0)
    GameOver(gameOverPin);
}

