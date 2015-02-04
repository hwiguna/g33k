// Scope Chords by Hari Wiguna, 2015
// Playing with R-2R Ladder to convert Digital to Analog
// This is TERRIBLE CODE.  Do not code like this! ;-)

int xPin0 = 2;
int yPin0 = A0;
int bitMax = 6;
const int countMax = 64; //128;

#define swap(a, b) { int16_t t = a; a = b; b = t; }

byte bitmap[countMax][8];

void setup() {
  //-- Setup output pins --
  for (byte b=0; b<bitMax; b++) {
    pinMode(xPin0+b, OUTPUT); 
    if (b==6) pinMode(10, OUTPUT); else pinMode(yPin0+b, OUTPUT);  
  } 

  //-- Clear bitmap --
  for (int y=0; y<countMax; y++)
    for (int x=0; x<8; x++)
      bitmap[y][x]=0;
      
  //-- Draw into bitmap --
  //drawPixel(0,63, 1);
  //drawLine(0,0, 63,63, 1);
  //drawLine(63,0, 0,63, 1);
  HariChord(31, 2.0*PI/20.0);
}

void loop() {
  //-- Cycle trhough ALL pixels in bitmap and plot ONLY the pixels that are "on" --
  for (int y=0; y<countMax; y++)
  {
    for (int x=0; x<countMax; x++)
    {
      if (bitRead(bitmap[y][x/8], x % 8))
        Plot(x,y);
    }
  }
}

//-- Output the proper voltages for X and Y --
// This could be improved significantly by manipulating PORTs directly instead of using Digita
void Plot(int x, int y)
{
  for (byte b=0; b<bitMax; b++) {
    digitalWrite(xPin0+b, bitRead(x,b));

    //if(b==6)
    // digitalWrite(10, bitRead(y,b));
    //else
      digitalWrite(yPin0+b, bitRead(y,b));
  }
  //delayMicroseconds(50);

//  for (byte b=0; b<bitMax; b++) {
//    digitalWrite(xPin0+b, 0);
//    if(b==6)
//      digitalWrite(10,0);
//    else
//      digitalWrite(yPin0+b,0);
//  }
//  
//  delay(1);
}


void HariChord(int rad, float rot)
{
  byte n = 5;
  int x[n];
  int y[n];
  for (byte i=0; i<n; i++)
  {
    float a = rot + i * 2 * PI / n;
    x[i] = 31 + cos(a)*rad;
    y[i] = 31 + sin(a)*rad;
  }
  
  //display.clearDisplay();
  for (byte i=0; i<(n-1); i++)
  {
    for (byte j=i+1; j<n; j++)
    {
      drawLine(x[i], y[i], x[j],y[j], 1);
    }
  }
  //display.display();
}

void drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if (color==0)
    bitClear(bitmap[y][x/8], x % 8);
  else
    bitSet(bitmap[y][x/8], x % 8);
}

// Bresenham's line drawing from wikipedia via AdaFruit
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } 
  else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } 
    else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


