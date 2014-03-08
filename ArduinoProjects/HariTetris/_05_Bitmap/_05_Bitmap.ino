
// Towards Arduino Tetris

// In this sketch, I want to create a 16x16 bitmap, be able to draw onto it, and have it reflect on the LED matrix.
// Eventually, I want to do the refresh in an interrupt routine so refresh rate won't be affected by any game logic.
// However, for now, let's keep it simple and not deal with interrupts yet.

// The 16x16 bitmap.  Each array element is a row (16 pixels on the X axis). 0,0 is bottom left of LED matrix.
int bitmap[16]; 

//-- Shift register pins --
const byte Row_RCLK = 11;   // Register Clock: Positive edge triggers shift register to output (White wire)
const byte Row_SRCLK = 12;  // Shift Register Clock: Positive edge triggers SER input into shift register (Yellow wire)
const byte Row_SER = 13;    // Serial input, read in on positive edge of SRCLK (Blue wire)

const byte Col_RCLK =5;   // Register Clock: Positive edge triggers shift register to output (White wire)
const byte Col_SRCLK = 6;  // Shift Register Clock: Positive edge triggers SER input into shift register (Yellow wire)
const byte Col_SER = 7;    // Serial input, read in on positive edge of SRCLK (Blue wire)

int twoBytes;

void setup() {
  // put your setup code here, to run once:
  pinMode(Row_RCLK,OUTPUT);
  pinMode(Row_SRCLK,OUTPUT);
  pinMode(Row_SER,OUTPUT);

  pinMode(Col_RCLK,OUTPUT);
  pinMode(Col_SRCLK,OUTPUT);
  pinMode(Col_SER,OUTPUT);

  //DiagonalLine();
}

// I drew a line from 0,0 to 15,15 to confirm that 0,0 is at bottom left corner.
// It turned out that it was at bottom right corner.  I adjusted WriteX and WriteY so now 0,0 is at bottom left.
void DiagonalLine() {
  ClearBitmap();
  for (byte i=0; i<16; i++) {
    PlotDot(i,i, 1);
  }
}

// I wrote this test to see if there's noticible dimming when a row has two LEDs lit vs all 16 lit.
// Thankfully, no noticible difference. :-)
void Triangle(bool isUpsideDown) {
  ClearBitmap();
  for (byte y=0; y<=7; y++) {
    for (byte x = (y); x <= (15-y); x++) {
      if (isUpsideDown)
        PlotDot(x,15-y, 1);
      else
        PlotDot(x,y, 1);
    }
  }
}

void loop() {
  Triangle(true);
  for (int d=0; d<50; d++)
    Refresh();

  Triangle(false);
  for (int d=0; d<50; d++)
    Refresh();
}

void Refresh() {
  for (byte r=0; r<16; r++) {
    // Turn off all X bits before turning on the row, so we won't get shadowing of the previous X pattern    
    twoBytes = 0;
    WriteX( highByte(twoBytes), lowByte(twoBytes) );

    // Turn on ONE row at a time
    twoBytes = 0;
    bitSet(twoBytes,r);
    twoBytes = ~twoBytes; // Rows need to be pulled to negative.  So invert before pushing bits to shift registers
    WriteY( highByte(twoBytes), lowByte(twoBytes) );

    // Now that the row is on, turn on the appropriate bit pattern for that row.
    twoBytes = bitmap[r];
    WriteX( highByte(twoBytes), lowByte(twoBytes) );

    // Let humans enjoy that row pattern for a few microseconds.
    delayMicroseconds(400);
  }
}

void WriteY(byte hiByte, byte loByte) {
  digitalWrite(Row_RCLK, LOW);
  shiftOut(Row_SER, Row_SRCLK, LSBFIRST, loByte); // When sending LSBFirst, send loByte, then HiByte
  shiftOut(Row_SER, Row_SRCLK, LSBFIRST, hiByte);
  digitalWrite(Row_RCLK, HIGH);
};

void WriteX(byte hiByte, byte loByte) {
  digitalWrite(Col_RCLK, LOW);
  shiftOut(Col_SER, Col_SRCLK, MSBFIRST, hiByte); // When sending MSBFirst, send hiByte, then loByte
  shiftOut(Col_SER, Col_SRCLK, MSBFIRST, loByte);
  digitalWrite(Col_RCLK, HIGH);
};

void ClearBitmap() {
  for (byte r=0; r<16; r++) {
    bitmap[r] = 0;
  }
}

void PlotDot(byte x, byte y, byte isOn) {
  if (isOn)
    bitSet(bitmap[y], x);
  else
    bitClear(bitmap[y], x);
}
