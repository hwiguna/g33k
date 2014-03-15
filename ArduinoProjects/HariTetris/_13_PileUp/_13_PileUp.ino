
// Towards Arduino Tetris

// v0.13 - Dropped pieces now pile up when it can't go down further.
// v0.12 - _12_CollisionDetection.  There are now three bitmaps: one contains the borders, another is the shape being manipulated, and last represents the LED matrix.
// v0.11 - Use _11_AccelerometerToButtons to tweak max-min values to make the control feels right
// v0.10 - Let's control shapes with accelerometer input (using only X and Y)
// v0.9 - Discovered that analogRead(A3) always returns 0 when timer is enabled?!
// v0.8 - 
// v0.7 - Finally, draw Tetris shapes!

// The 16x16 bitmap.  Each array element is a row (16 pixels on the X axis). 0,0 is bottom left of LED matrix.
int screen[16]; // Represents final bitmap shown on the LED Matrix
int boardLayer[16]; // This is the whole board minus the current shape controlled by user.
int shapeLayer[16]; // This is the size of the whole board, but only contains the shape at its "next" location.

//-- Shift register pins --
const byte Row_RCLK = 11;   // Register Clock: Positive edge triggers shift register to output (White wire)
const byte Row_SRCLK = 12;  // Shift Register Clock: Positive edge triggers SER input into shift register (Yellow wire)
const byte Row_SER = 13;    // Serial input, read in on positive edge of SRCLK (Blue wire)

const byte Col_RCLK =5;   // Register Clock: Positive edge triggers shift register to output (White wire)
const byte Col_SRCLK = 6;  // Shift Register Clock: Positive edge triggers SER input into shift register (Yellow wire)
const byte Col_SER = 7;    // Serial input, read in on positive edge of SRCLK (Blue wire)

const int xSensor = A4; // x refers to game x, A4 is actually connected to accelerometer Y axis
const int ySensor = A5;

int twoBytes;
int cycles = 0;
byte currentRotation = 0; // 0..3 clockwise rotation
int currentX = 6; // No such thing as a signed byte :-(
int currentY = 12;
int currentShape = 0;
int xSaved = currentX;
int ySaved = currentY;
int rotateDelay = 1;
int dropDelay = 1;

//=== Tetris Shapes ===
// Each row of this array represents one 4x4 shape in all its four rotations.
// I used a spreadsheet to convert bitmap bit patterns into the hex numbers below.
int shapes[][4] = {
  { 0x0000, 0x4404, 0xE6EC, 0x444},   // 0. T
  { 0x0000, 0x0808, 0x6C6C, 0xC4C4},  // 1. S
  { 0x0000, 0x0404, 0xCCCC, 0x6868},  // 2. Z
  { 0x0000, 0x40C0, 0x4E42, 0x684E},  // 3. L
  { 0x0000, 0x2060, 0x284E, 0x6E42},  // 4. J
  { 0x0000 ,0x0000, 0x6666, 0x6666},  // 5. O
  { 0x4040, 0x4040, 0x4F4F, 0x4040},  // 6. I
//  { 0x0001, 0x0022, 0x0444, 0x8888},
//  { 0x0000, 0x0000, 0x000, 0x8CEF}
};

//=== Tetris shape & board routines ===

unsigned int GetShapeRow(byte whichShape, byte whichRotation, byte row) {
  unsigned int shape = 0xF000 & (shapes[whichShape][row] << (4*whichRotation) );
  return shape;  
}

void DrawShape(int* bitmap, byte whichShape, byte whichRotation, byte xOffset, byte yOffset) {
  for (byte r=0; r<4; r++) {
    unsigned int shape = GetShapeRow(whichShape, whichRotation, r);
    shape = shape >> (xOffset);
    byte bitmapY = 3-r+yOffset;
    bitmap[bitmapY] = bitmap[bitmapY] | shape;
  }
}

void UpdateBoard() {
  int xValue = analogRead(xSensor);
  int yValue = analogRead(ySensor);
    
  const int yMax = 250; // Top-down = Rotate
  const int yMin = 185; // Top-up = Drop piece
  
  const int xMax = 390; // Right-down = Shift right
  const int xMin = 330; // Left-down = shift left
  
  int xOffset = 0;
  int yOffset = 0;
  if (yValue > yMax) yOffset++;
  if (yValue < yMin) yOffset--;
  if (yOffset==0) {
    if (xValue > xMax) xOffset++;
    if (xValue < xMin) xOffset--;
  }

  // Moving up is actually "rotate"
  if (yOffset==1) {
    //yOffset=0;
    if ( (rotateDelay--) == 0) {
      rotateDelay = 2;
      currentRotation++;
      if (currentRotation>3) currentRotation = 0;
    }
  }
  
//  xOffset = DetectHorizontalCollisions(currentX, xOffset);
  xSaved = currentX;
  currentX += xOffset;
  if (dropDelay-- == 0) {
    dropDelay=3;
    ySaved = currentY;
    currentY -= 1;
  }

  ClearBitmap(shapeLayer);
  DrawShape(shapeLayer, currentShape,currentRotation, currentX, currentY);
  if ( HasCollision(shapeLayer, boardLayer) ) {
    // If collided with something while moving sideways, revert X position
    if ( xOffset != 0 ) {
      currentX = xSaved;
    } else {
      // We hit something while falling
      currentY = ySaved;
    
      // Collided vertically, copy the piece at it's non-moved location to boardLayer
      if ( true ) { //xOffset==0 && yOffset!=1 ) {
        DrawShape(boardLayer, currentShape,currentRotation, xSaved, ySaved);
        CopyBitmap(boardLayer, screen);
        currentX=6;
        currentY = 12;
        currentShape = random( sizeof(shapes)/(4*sizeof(int)) );
      }
    }
  } else {
    CopyBitmap(boardLayer, screen);
    OverlayBitmap(shapeLayer, screen);
  }
}

void NewGame() {
  ClearBitmap(boardLayer);
  DrawBoard(boardLayer);
}

void DrawBoard(int* bitmap) {
  for (byte r=0; r<16; r++) {
      PlotDot(bitmap, 0, r, 1);
      PlotDot(bitmap, 15, r, 1);
      PlotDot(bitmap, r,0, 1);
  }
}

//=== Bitmap Utilities ===

void ClearBitmap(int* bitmap) {
  for (byte r=0; r<16; r++) {
    bitmap[r] = 0;
  }
}

void PlotDot(int* bitmap, byte x, byte y, byte isOn) {
  if (isOn)
    bitSet(bitmap[y], x);
  else
    bitClear(bitmap[y], x);
}

void CopyBitmap(int* sourceLayer, int* targetLayer) {
  memcpy(targetLayer, sourceLayer, sizeof(screen));
}

void OverlayBitmap(int* topLayer, int* targetLayer) {
  for (byte r=0; r<16; r++) {
    targetLayer[r] |= topLayer[r];
  }
}

bool HasCollision(int* bitmap1, int* bitmap2) {
  // Take two bitmaps: boardLayer (walls and accumulated shapes), and shapeLayer (shape being tested)
  // If any of the rows has common bits between the two bitmaps, we have a collision!
  bool hasCollision = false;
  for (byte r=0; r<16; r++) {
    if ((bitmap1[r] & bitmap2[r]) != 0) {
      hasCollision=true;
      break;
    }
  }
  return hasCollision;
}

//=== LED Matrix routines ===

void RefreshScreen(int* bitmap) {
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
    delayMicroseconds(300); // was 400
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
  shiftOut(Col_SER, Col_SRCLK, LSBFIRST, loByte);
  shiftOut(Col_SER, Col_SRCLK, LSBFIRST, hiByte); // When sending MSBFirst, send hiByte, then loByte
  digitalWrite(Col_RCLK, HIGH);
};

//=== SETUP ===

void setup() {
  SetupShiftRegisterPins();
  SetupInterruptRoutine();
}

void SetupInterruptRoutine() {
  cli(); // Stop interrupts

  TCCR0A = 0; // 
  TCCR0B = 0;
  TCNT0 = 0; // Counter
  
  // compare match register = [ 16,000,000Hz/ (prescaler * desired interrupt frequency) ] - 1
  OCR0A = 255; //(16*10^6) / (2000*64) - 1; // OCR0A/OCR02A can be up to 255, OCR1A up to 65535
  
  TCCR0A |= (1 << WGM01); // Turn on CTC mode
  TCCR0B |= (1 << CS01) | (1 << CS00); // turn on bits for 64 prescaler
  
  TIMSK0 |= (1 << OCIE0A); // enable timer compare interrupt
  
  sei(); // allow interrupts
}

ISR(TIMER0_COMPA_vect)
{
  cycles++;
  RefreshScreen( screen );
  
  if ((cycles % 5) == 0)
    UpdateBoard();
}


void SetupShiftRegisterPins() {
  pinMode(Row_RCLK,OUTPUT);
  pinMode(Row_SRCLK,OUTPUT);
  pinMode(Row_SER,OUTPUT);

  pinMode(Col_RCLK,OUTPUT);
  pinMode(Col_SRCLK,OUTPUT);
  pinMode(Col_SER,OUTPUT);
  
  NewGame();
}

void loop() {
}

