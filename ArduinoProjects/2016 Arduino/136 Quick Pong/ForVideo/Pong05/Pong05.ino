// Arduino Pong by Hari Wiguna, 2016
// v0.0 - draw ball
// v0.1 - move ball
// v0.2 - using millis(), move in Y direction too
// v0.3 - Paddles!
// v0.4 - Collision Detection
// v0.5 - Scoring, Speed up, and Sound

#include "U8glib.h"

//== Preferences ==
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10); // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10
int paddle0Pin = A1; // Left player potentiometer
int paddle1Pin = A0; // Right player potentiometer
int winningScore = 3; // How high before we declare a winner?
byte tonePin = 2; // Which digital pin the beeper is attached to
int animationSpeed0 = 25; // Initial speed of each round (lower = faster)

//== Game Variables ==
u8g_uint_t courtWidth, courtHeight, halfCourtWidth;
u8g_uint_t ballSize = 4;
u8g_uint_t ballX;
u8g_uint_t ballDirectionX = 1;
u8g_uint_t ballY;
u8g_uint_t ballDirectionY = 1;
u8g_uint_t paddleWidth = 2;
u8g_uint_t paddleHeight = 8;
u8g_uint_t paddleHalfHeight = paddleHeight/2;
u8g_uint_t paddle0Y; // Left player vertical paddle position
u8g_uint_t paddle1Y; // Right player vertical paddle position

int score0, score1; // Left & Right player's scores
bool gameOver = false;

int bounceToneFrequency = 523;
int bounceToneDuration = 62;
int missToneFrequency = 523 / 2;
int missToneDuration = 512;

unsigned long timeToMove; // When should we move the ball again?
int animationSpeed = animationSpeed0; // Current ball speed (lower = faster)

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
  char strScore0[] = "?"; // Sets string length to 1
  char strScore1[] = "?";
  strScore0[0] = '0' + score0; // Overide the string value with single digit score
  strScore1[0] = '0' + score1;
  u8g.setFont(u8g_font_04b_03b);
  u8g_uint_t scoreWidth = u8g.getStrPixelWidth(strScore0);
  const int offset = 5;
  u8g_uint_t scoreY = 9;
  u8g.drawStr( halfCourtWidth - offset - scoreWidth, scoreY, strScore0);
  u8g.drawStr( halfCourtWidth + offset, scoreY, strScore1);
}

void DrawGameOver()
{
  u8g.setFont(u8g_font_timB18);
  u8g.setFontPosCenter(); // vertical alignment
  char gameStr[] = "Game";
  char overStr[] = "Over";
  u8g_uint_t gx = (courtWidth - u8g.getStrPixelWidth(gameStr)) / 2;
  u8g_uint_t ox = (courtWidth - u8g.getStrPixelWidth(overStr)) / 2;
  u8g.drawStr(gx, 20, gameStr);
  u8g.drawStr(ox, 40, overStr);
}

void DrawCourt()
{
  u8g.drawHLine(0, 0, courtWidth);
  u8g.drawHLine(0, courtHeight - 1, courtWidth);
  byte dash = 3;
  for (byte y = 0; y < (courtHeight / dash / 2); y++)
  {
    u8g.drawVLine(halfCourtWidth - 1, 2 + y * dash * 2, dash);
  }
}

void Player0Missed()
{
  // When left player missed, move the ball just to the left of rightmost of court
  ballX = courtWidth - ballSize - 1;
  ballY = paddle1Y + paddleHalfHeight; // ball will be served at location of player 1's paddle
  tone(tonePin, missToneFrequency, missToneDuration);
  delay(1000);
  score1++;
  animationSpeed = animationSpeed0;
  if (score1 == winningScore) gameOver = true;
}

void Player1Missed()
{
  // When right player missed, move the ball just to the right of the leftmost of court
  ballX = 1;
  ballY = paddle0Y + paddleHalfHeight; // ball will be served at location of player 0's paddle
  tone(tonePin, missToneFrequency, missToneDuration);
  delay(1000);
  score0++;
  animationSpeed = animationSpeed0;
  if (score0 == winningScore) gameOver = true;
}

void BounceX()
{
  tone(tonePin, bounceToneFrequency, bounceToneDuration);
  ballDirectionX = -ballDirectionX;
  animationSpeed--; // Speed up game with each bounce
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
      animationSpeed--; // Speed up game with each bounce
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
  halfCourtWidth = courtWidth / 2;
}

void loop(void) {
  u8g.firstPage();
  do {

    if (gameOver)
      DrawGameOver();
    else
      MoveBall();

    DrawCourt();
    DrawScores();
    u8g.drawBox(ballX, ballY, ballSize, ballSize);
    DrawPaddles();
  } while ( u8g.nextPage() );
}
