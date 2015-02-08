// Scope Chords by Hari Wiguna, 2015
// Playing with R-2R Ladder to convert Digital to Analog
// v4 uses direct port register manipulation, for much faster code
// v5 abandons the bitmap and relies on the scope to create a line
// v6 draws the dots in certain order so there are no random extra lines
// v7 bring back line drawing, but instead of drawing lines to bitmap, plot dot directly to scope
// v8 take out line drawing again, just plot the nodes.
// v9 put ALL the coordinates to be plotted in one long array to make the loop as fast as possible.

// X axis is on PORTB (least significant bit is on D8)
// Y axis is on PORTC (least significant bit is on A0)
int rad = 31;  // Radius
float rot = 0; // rotation angle in radians
const int n = 3;
int x[n];
int y[n];
int xx[3];
int yy[3];

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define swap(a, b) { int16_t t = a; a = b; b = t; }

void setup() {
  //To set the port directions (PinMode) of the low six bits as output
  //and not touch the high two bits, we use a bit OR.
  DDRB = DDRB | B00111111; // Set bottom 6 bits as outout while leaving the top two alone
  DDRC = DDRC | B00111111; // Set bottom 6 bits as outout while leaving the top two alone

  HariChordCalculations();
  delay(2000);
  cbi (TIMSK0,TOIE0);
}

void loop() {
    HariChordDraw0();
    //DrawTriangle();
    //Sawtooth();
}

void HariChordCalculations()
{
  for (byte i=0; i<n; i++)
  {
    float a = rot + i * 2 * PI / n;
    x[i] = 31 + cos(a)*rad;
    y[i] = 31 + sin(a)*rad;
    xx[i] = x[i];
    yy[i] = y[i];
  }
}

void DrawTriangle()
{
  for (int i=0; i<1000; i++)
  {
  Plot(0,0);
  //Plot(0,63);
  Plot(63,63);
  //Plot(0,0);
  }
  //Plot(0,0);
//  Plot(xx[0], yy[0]);
//  Plot(xx[1], yy[1]);
//  Plot(xx[2], yy[2]);
//  Plot(xx[0], yy[0]);

//  for (byte i=0; i<3; i++)
//  {
//    //Plot(xx[i], yy[i]);
//    PORTB = (PORTB & B11000000) | (xx[i] & B00111111);
//    PORTC = (PORTC & B11000000) | (yy[i] & B00111111);
//
//  }
  //Plot(xx[0], yy[0]);
}

void Sawtooth()
{
  for (byte i=0; i<64; i++)
  {
    Plot(i, 63-i);
  }
}

void HariChordDraw0()
{
  for (int rep=0; rep<1000; rep++)
  {
    for (byte i=0; i<(n-1); i++)
    {
      for (byte j=i+1; j<n; j++)
      {
        Plot(x[i], y[i]);
        Plot(x[j], y[j]);
        Plot(x[i], y[i]);
      }
    }
  }
}

//-- Output the proper voltages for X and Y --
void Plot(byte x, byte y)
{
//  PORTB = (PORTB & B11000000) | (x & B00111111);
//  PORTC = (PORTC & B11000000) | (y & B00111111);
  PORTB = x; //(x & B00111111);
  PORTC = y; //(y & B00111111);
  //for (int d=0; d<32000; d++) {int x = 2^16;}
  delayMicroseconds(500);
  //delay(10);
} 

