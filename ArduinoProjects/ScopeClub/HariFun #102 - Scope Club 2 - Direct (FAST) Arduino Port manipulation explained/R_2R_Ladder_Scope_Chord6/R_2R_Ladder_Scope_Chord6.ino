// Scope Chords by Hari Wiguna, 2015
// Playing with R-2R Ladder to convert Digital to Analog
// v4 uses direct port register manipulation, for much faster code
// v5 abandons the bitmap and relies on the scope to create a line
// v6 draws the dots in certain order so there are no random extra lines

// X axis is on PORTB (least significant bit is on D8)
// Y axis is on PORTC (least significant bit is on A0)
int rad = 31;  // Radius
float rot = 0; // rotation angle in radians
const int n = 7;
int x[n];
int y[n];

void setup() {
  //To set the port directions (PinMode) of the low six bits as output
  //and not touch the high two bits, we use a bit OR.
  DDRB = DDRB | B00111111; // Set bottom 6 bits as outout while leaving the top two alone
  DDRC = DDRC | B00111111; // Set bottom 6 bits as outout while leaving the top two alone

  HariChordCalculations();
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
  PORTB = (PORTB & B11000000) | (x & B00111111);
  PORTC = (PORTC & B11000000) | (y & B00111111);
  delayMicroseconds(10);
  //delay(500);
}


void HariChord()
{
  for (byte jump=1; jump < 2; jump++)
  {
    Plot(x[0], y[0]); // Go to zeroeth node
    byte node = n;
    do
    {
      node += jump; // compute next node
      if (node>=n) node-=n; // wrap around if computed node is beyond the max
      Plot(x[node], y[node]); // plot next node
    } while (node != 0); // Keep going until we've come full circle
  }
}

