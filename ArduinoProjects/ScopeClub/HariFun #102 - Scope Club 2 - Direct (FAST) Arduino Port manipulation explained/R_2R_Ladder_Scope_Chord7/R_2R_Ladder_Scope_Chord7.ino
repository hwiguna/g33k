// Scope Chords by Hari Wiguna, 2015
// Playing with R-2R Ladder to convert Digital to Analog
// v4 uses direct port register manipulation, for much faster code
// v5 abandons the bitmap and relies on the scope to create a line
// v6 draws the dots in certain order so there are no random extra lines
// v7 bring back line drawing, but instead of drawing lines to bitmap, plot dot directly to scope

// X axis is on PORTB (least significant bit is on D8)
// Y axis is on PORTC (least significant bit is on A0)
int rad = 31;  // Radius
float rot = 0; // rotation angle in radians
const int n = 5;
int x[n];
int y[n];


#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define swap(a, b) { int16_t t = a; a = b; b = t; }

void setup() {
  //To set the port directions (PinMode) of the low six bits as output
  //and not touch the high two bits, we use a bit OR.
  DDRB = DDRB | B00111111; // Set bottom 6 bits as outout while leaving the top two alone
  DDRC = DDRC | B00111111; // Set bottom 6 bits as outout while leaving the top two alone

  delay(2000); // This is here just in case TX/RX got messed up by main loop. I still want to be able to reprogram the Arduino.
  
  HariChordCalculations();
  
  cbi (TIMSK0,TOIE0); // Turn off Interrupts
}

void loop() {
  HariChord();
}

void HariChordCalculations()
{
  for (byte i=0; i<n; i++)
  {
    float a = rot + i * 2 * PI / n;
    x[i] = 31 + cos(a)*rad;
    y[i] = 31 + sin(a)*rad;
  }
}

//-- Output the proper voltages for X and Y --
void Plot(int x, int y)
{
//  PORTB = (PORTB & B11000000) | (x & B00111111);
//  PORTC = (PORTC & B11000000) | (y & B00111111);
  PORTB = x; //(x & B00111111);
  PORTC = y; //(y & B00111111);
  delayMicroseconds(50);
  //delay(10);
}


void HariChord()
{
//for (int rep=0; rep<1000; rep++)
  {
    for (byte i=0; i<(n-1); i++)
    {
      for (byte j=i+1; j<n; j++)
      {
        drawLine(x[i], y[i], x[j],y[j], 1);
      }
    }
  }
}


void HariChord1()
{
  for (byte jump=1; jump < 2; jump++)
  {
    int i = 0;
    byte node = n;
    do
    {
      node += jump; // compute next node
      if (node>=n) node-=n; // wrap around if computed node is beyond the max
      drawLine(x[i], y[i], x[node], y[node], 1); // plot next node
      i = node;
    } while (node != 0); // Keep going until we've come full circle
  }
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
      Plot(y0, x0);
    } 
    else {
      Plot(x0, y0);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

