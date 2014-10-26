//
// Hari Suduino, Oct 2014
// Huge thank you to AdaFruit for the libraries!

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(8,9,10,11,12);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

//#define NUMFLAKES 10
//#define XPOS 0
//#define YPOS 1
//#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

const byte col3Pin = A0; // Analog pins A3..A0 = Col0..Col3.  I wanted the wiring to be pretty, that's why this is reversed.
const byte row0Pin = 6;  // Digital pins D6..D9 = Row0..Row3
const char keys[][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};

char board[9][9];

//-- Cursor --
int8_t cursorX = 0;
int8_t cursorY = 0;
unsigned long timeToUpdateCursor = millis();
bool cursorIsShown = false;

void setup()   {
  Serial.begin(9600);
  SetupScreen();
  SetupKeypad();
  SetupBoard();

  //TestPattern();
  DrawBoard();
}


void loop() {
  ScanKeypad();
  RefreshCursor();
}

void RefreshCursor()
{
  if (millis() > timeToUpdateCursor) {
    cursorIsShown = !cursorIsShown;

//    Serial.print("cursorX="); Serial.print(cursorX);
//    Serial.print(" cursorY="); Serial.print(cursorY);
//    Serial.print(" cursorIsShown="); Serial.println(cursorIsShown);

    if (cursorIsShown)
      DrawCursor(cursorX, cursorY);
    else
      ReDrawCell();
    display.display();
    
    timeToUpdateCursor = millis() + 250; 
  }
}

void ReDrawCell()
{
  EraseCell(cursorX, cursorY);
  DrawCell(cursorX, cursorY);
}

void SetupBoard()
{
  for (byte r=0; r<9; r++)
  {
    for (byte c=0; c<9; c++)
    {
      board[r][c] = '*';
    }
  }
}

void SetupScreen()
{
  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(60);
  display.clearDisplay();   // clears the screen and buffer
  display.setRotation(3);  // rotate 90 degrees counter clockwise, can also use values of 2 and 3 to go further.
}


void SetupKeypad()
{
  for (byte index=0; index<4; index++)
  {
    pinMode(col3Pin+index, OUTPUT);
    digitalWrite(col3Pin+index, HIGH);
    pinMode(row0Pin+index, INPUT_PULLUP);
  }
}

void ScanKeypad()
{
  // Power up one column at a time
  for (byte col=0; col<4; col++)
  {
    digitalWrite(col3Pin+col, LOW); // LOW = ON
    // Check to see if that power made it to one of the rows
    for (byte row=0; row<4; row++)
    {
      byte val = digitalRead(row0Pin+row);
      if (val==LOW) {
        //Serial.print("row="); Serial.print(row);
        //Serial.print(" col="); Serial.print(3-col);
        //Serial.print(" key="); Serial.println(keys[row][3-col]);
        ProcessKeypress(keys[row][3-col]);
        delay(200);
      }
    }
    digitalWrite(col3Pin+col, HIGH); // LOW = OFF
  }
}

void ProcessKeypress(char key)
{
  switch (key)
  {
    case 'A': MoveCursor(+1,0); break;
    case 'B': MoveCursor(-1,0); break;
    case 'C': MoveCursor(0,-1); break;
    case 'D': MoveCursor(0,+1); break;
    default: SetCell(cursorX,cursorY, key); break;
  }
}

void MoveCursor(int8_t xD, int8_t yD)
{
  //-- Replace cursor with the digit before moving cursor --
  if (cursorIsShown) {
    ReDrawCell();
    display.display();
  }
  
  cursorX += xD;
  cursorY += yD;
  if (cursorX>8) cursorX=0;
  if (cursorX<0) cursorX=8;
  if (cursorY>8) cursorY=0;
  if (cursorY<0) cursorY=8;
}

void SetCell(byte x, byte y, char val)
{
  board[x][y] = val;
  //DrawCell(x,y);
}

void EraseCell(byte x, byte y)
{
  byte x0 = x*5 + CellOffset(x);
  byte y0 = y*6 + CellOffset(y);
  display.fillRect(x0, y0, 4,5, WHITE);
}

void DrawCursor(byte x, byte y)
{
  byte x0 = x*5 + CellOffset(x);
  byte y0 = y*6 + CellOffset(y);
  display.fillRect(x0, y0, 4,5, BLACK);
}

byte CellOffset(byte x)
{
  return ((x>2) ? 2 : 0) + ((x>5) ? 2 : 0);
}

void TestPattern()
{
  byte num = 1;
  for (byte x=0; x<9; x++)
  {
    //byte xD = ((x>2) ? 2 : 0) + ((x>5) ? 2 : 0); //TODO: replace with CellOffset
    for (byte y=0; y<9; y++)
    {
      //byte yD = ((y>2) ? 2 : 0) + ((y>5) ? 2 : 0); //TODO: replace with CellOffset
      num = random(1,9);
      DrawCell(x,y, num);
    }
  }
  display.display();
}

void DrawBoard()
{
  byte num = 1;
  for (byte x=0; x<9; x++)
  {
    //byte xD = ((x>2) ? 2 : 0) + ((x>5) ? 2 : 0);
    for (byte y=0; y<9; y++)
    {
      //byte yD = ((y>2) ? 2 : 0) + ((y>5) ? 2 : 0);
      num = random(1,9);
      DrawCell(x,y, '*');
    }
  }
  display.display();
}

void DrawCell(int16_t x, int16_t y)
{
  DrawCell(x, y, board[x][y]);
}

void DrawCell(int16_t x, int16_t y, char ch)
{
  x = x*5 + CellOffset(x); 
  y = y*6 + CellOffset(y); 
  int16_t w=3;
  int16_t h=4;
  uint16_t color = BLACK;

  switch (ch)
  {
  case '0':
    display.drawRect(x,y, w+1,h+1, color);
    break;
  case '1':
    display.drawLine(x+2,y, x+2, y+h, color);
    break;
  case '2':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    display.drawLine(x,y+h, x+w, y+h, color);
    // verticals
    display.drawLine(x+w,y, x+w, y+2, color);
    display.drawLine(x,y+h-2, x, y+h, color);
    break;
  case '3':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    display.drawLine(x,y+h, x+w, y+h, color);
    // verticals
    display.drawLine(x+w,y, x+w, y+h, color);
    break;
  case '4':
    // horizontals
    display.drawLine(x,y+2, x+w, y+2, color);
    // verticals
    display.drawLine(x,y, x, y+2, color);
    display.drawLine(x+w,y, x+w, y+h, color);
    break;
  case '5':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    display.drawLine(x,y+h, x+w, y+h, color);
    // verticals
    display.drawLine(x,y, x, y+2, color);
    display.drawLine(x+w,y+h-2, x+w, y+h, color);
    break;
  case '6':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    display.drawLine(x,y+h, x+w, y+h, color);
    // verticals
    display.drawLine(x,y, x, y+h, color);
    display.drawLine(x+w,y+h-2, x+w, y+h, color);
    break;
  case '7':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    // verticals
    display.drawLine(x+w,y, x+w, y+h, color);
    break;
  case '8':
    display.drawRect(x,y, w+1,h+1, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    break;
  case '9':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    display.drawLine(x,y+h, x+w, y+h, color);
    // verticals
    display.drawLine(x,y, x, y+2, color);
    display.drawLine(x+w,y, x+w, y+h, color);
    break;
  case '*':
//    display.drawPixel(x,y, color);
//    display.drawPixel(x,y+h, color);
//    display.drawPixel(x+w,y, color);
//    display.drawPixel(x+w,y+h, color);
    display.drawLine(x+1,y+2, x+2, y+2, color);
    break;
  default:
    display.drawRect(x,y, w+1,h+1, color);
    break;
  }
}

