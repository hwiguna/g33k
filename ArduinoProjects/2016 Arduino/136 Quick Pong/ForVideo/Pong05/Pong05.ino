// Arduino Pong by Hari Wiguna, 2016
// v0.0 - draw ball
// v0.1 - move ball
// v0.2 - using millis(), move in Y direction too
// v0.3 - Paddles!
// v0.4 - Collision Detection
// v0.5 - Scoring & Sound

#include "U8glib.h"

//== Preferences ==
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10); // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10
int paddle0Pin = A1;
int paddle1Pin = A0;
int winningScore = 2;
byte tonePin = 2;

//== Game Variables ==
u8g_uint_t courtWidth, courtHeight;
u8g_uint_t ballSize = 4;
u8g_uint_t ballX;
u8g_uint_t ballDirectionX = 1;
u8g_uint_t ballY;
u8g_uint_t ballDirectionY = 1;
u8g_uint_t paddleWidth = 2;
u8g_uint_t paddleHeight = 8;
u8g_uint_t paddle0Y;
u8g_uint_t paddle1Y;
int score0;
int score1;
bool gameOver = false;
int bounceToneFrequency = 523;
int bounceToneDuration = 62;
int missToneFrequency = 523/2;
int missToneDuration = 512;

unsigned long timeToMove;
int animationSpeed = 20;

bool MissedPaddle(u8g_uint_t py)
{
  u8g_uint_t ballTop = ballY;
  u8g_uint_t ballBottom = ballY + ballSize - 1;
  u8g_uint_t paddleTop = py;
  u8g_uint_t paddleBottom = py + paddleHeight - 1;
  return ballBottom < paddleTop || ballTop > paddleBottom;
}

void DrawScores()
{
  char strScore0[2] = " ";
  char strScore1[2] = " ";
  strScore0[0] = '0' + score0;
  strScore1[0] = '0' + score1;
  int scoreWidth = u8g.getStrPixelWidth(strScore0);
  const int offset = 5;
  int scoreY = 9;
  int halfCourtWidth = courtWidth / 2;
  u8g.drawStr( halfCourtWidth - offset - scoreWidth, scoreY, strScore0);
  u8g.drawStr( halfCourtWidth + offset, scoreY, strScore1);
}

void DrawGameOver()
{
  u8g.drawStr( 0, 20, "Game Over");
}

void Player0Missed()
{
  // When left player missed, move the ball just to the left of rightmost of court
  ballX = courtWidth - ballSize - 1;
  ballY = paddle1Y; // ball will be served at location of player 1's paddle
  tone(tonePin, missToneFrequency, missToneDuration);
  delay(2000);
  score1++;
  if (score1 == winningScore) gameOver = true;
}

void Player1Missed()
{
  // When right player missed, move the ball just to the right of the leftmost of court
  ballX = ballSize;
  ballY = paddle0Y; // ball will be served at location of player 0's paddle
  tone(tonePin, missToneFrequency, missToneDuration);
  delay(2000);
  score0--;
  if (score0 == winningScore) gameOver = true;
}

void BounceX()
{
  ballDirectionX = -ballDirectionX;
  tone(tonePin, bounceToneFrequency, bounceToneDuration);
}

void MoveBall()
{
  if (millis() > timeToMove) {
    ballX += ballDirectionX;
    if (ballX <= 0)
        if (MissedPaddle(paddle0Y)) Player0Missed(); else BounceX();

    if (ballX >= (courtWidth - ballSize))
        if (MissedPaddle(paddle1Y)) Player1Missed(); else BounceX();

    ballY += ballDirectionY;
    if (ballY >= (courtHeight - ballSize) || ballY <= 0) {
      ballDirectionY = -ballDirectionY;
      tone(tonePin, bounceToneFrequency, bounceToneDuration);
    }

    timeToMove = millis() + animationSpeed;
  }
}

void DrawPaddle(u8g_uint_t paddleX, int paddleY)
{
  u8g.drawBox(paddleX, paddleY, paddleWidth, paddleHeight);
}

void DrawPaddles()
{
  paddle0Y = map(analogRead(paddle0Pin), 0, 1023, 0, courtHeight - paddleHeight);
  paddle1Y = map(analogRead(paddle1Pin), 0, 1023, 0, courtHeight - paddleHeight);

  DrawPaddle(0, paddle0Y);
  DrawPaddle(courtWidth - paddleWidth, paddle1Y);
}

void setup(void) {
  u8g.setRot180();  // flip screen
  courtWidth = u8g.getWidth();
  courtHeight =  u8g.getHeight();
}

void loop(void) {
  u8g.firstPage();
  do {
    if (gameOver)
      DrawGameOver();
    else
    {
      MoveBall();
      u8g.drawBox(ballX, ballY, ballSize, ballSize);
      DrawPaddles();
      DrawScores();
    }
  } while ( u8g.nextPage() );
}
