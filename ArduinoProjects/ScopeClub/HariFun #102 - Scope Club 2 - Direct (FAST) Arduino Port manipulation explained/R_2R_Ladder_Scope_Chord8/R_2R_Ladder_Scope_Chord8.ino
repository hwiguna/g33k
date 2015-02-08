// Scope Chords by Hari Wiguna, 2015
// Playing with R-2R Ladder to convert Digital to Analog
// v4 uses direct port register manipulation, for much faster code
// v5 abandons the bitmap and relies on the scope to create a line
// v6 draws the dots in certain order so there are no random extra lines
// v7 bring back line drawing, but instead of drawing lines to bitmap, plot dot directly to scope
// v8 take out line drawing again, just plot the nodes.

// X axis is on PORTB (least significant bit is on D8)
// Y axis is on PORTC (least significant bit is on A0)
int rad = 31;  // Radius
float rot = PI/4; // rotation angle in radians
const int n = 2;
int x[n];
int y[n];

#define swap(a, b) { int16_t t = a; a = b; b = t; }

void setup() {
  //To set the port directions (PinMode) of the low six bits as output
  //and not touch the high two bits, we use a bit OR.
  DDRB = DDRB | B00111111; // Set bottom 6 bits as outout while leaving the top two alone
  DDRC = DDRC | B00111111; // Set bottom 6 bits as outout while leaving the top two alone

  HariChordCalculations();
}

void loop() {
  HariChordDraw();
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

void HariChordDraw()
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

//-- Output the proper voltages for X and Y --
void Plot(int x, int y)
{
  PORTB = (PORTB & B11000000) | (x & B00111111);
  PORTC = (PORTC & B11000000) | (y & B00111111);
  //delayMicroseconds(10);
  //delay(10);
} 

