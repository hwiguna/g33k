/*
  Arduino 56x8 scrolling LED Matrix
  
Scrolls any message on up to seven (or more?) 8x8 LED matrices.
Adjust the bitmap array below to however many matrices you want to use. 
You can start with as few as two.

The circuit:
* 1 8-bit shift register (SN74HC595) to drive the rows of all displays.
* N power 8-bit shift registers (TPIC6C595) to drive the columns (1 chip per display)
* N 8x8 LED matrix display (rows=Anodes, cold=cathodes)
* N * 8 470ohm resistors, one for each column of each display
* 1 10K resistor
* A big breadboard, or several small ones
* Lots and lots of wires. AT LEAST 16 wires for each display.
* If you plan on driving more than 8 displays, you should add 8 transistors to drive the rows because
potentially you would be lighting up the whole row at one time (56 LEDs at once in my case, 8*n in your case)

Wiring tips:
* Key to success is to put the chips on the left and/or right of the matrix rather than above or below.
This would allow you to run wires above and below the matrix without covering any of them.
* I used several power bus breadboard strips above and below the matrix so all row wires never has to cross the matrix.
* Wire up each matrix one at a time, turning on the Ardunio to verify your work before proceeding to the next matrix.
Correcting your work after you have 32 wires over it is very difficult.
* Circuit is available at: 
http://g33k.blogspot.com/2010/02/arduino-56x8-scrolling-led-matrix.html

Created Feb 2010
By Hari Wiguna
http://g33k.blogspot.com/

Based on things I learn from the Arduino website.
Special credit to aspro648 creating the alphabet that I use.
http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1203747843/22

Creative Commons Attribution-Share Alike 3.0 United States License

*/
// I kept these version notes to show you that it doesn't just all magically happen.  I start simple and keep adding more.
//v01 - Just see if we can drive one matrix, one dot at a time.  Forget multiplexing for now.
//v02 - All three displays show same pattern because they are all tied to same data line.
//v03 - Second and third 595 inputs are tied to outputs of previous, so now shiftout three bytes instead of one.
//v04 - Let's multiplex.  This version has no bleeding, but still flickers quite a bit.
//v05 - Flicker is reduced by using delayMicroseconds() instead of delay().  Flipping both latches HIGH at same time increases brightess of all LEDs.
//v06 - let's animate! (none of this code is in v09, I removed them because they're unrelated to the marquee.
//v07 - We got a scrolling message marquee!
//v08 - Now with SEVEN matrices! 56x8 pixels
//v09 - Add comments and remove experimental code
//v10 - Fixed search and replace error in Plot.  Thanks to Capacea for catching this error.

//-- Columns (Negative Cathodes) --
int latchPin1 = 2; //Arduino pin connected to Green 10 RCK of TPIC6C595
int clockPin1 = 3; //Arduino pin connected to Yellow 15 SRCK of TPIC6C595
int dataPin1 = 4;  //Arduino pin connected to Blue 2 SER IN of TPIC6C595

//-- Rows (Positive Anodes) --
int latchPin2 = 5; //Arduino pinn connected to Green Latch 12 ST_CP / RCK of 74HC595
int clockPin2 = 6; //Arduino pin connected to Yellow Clock 11 SH_CP / SCK of 74HC595
int dataPin2 = 7;  //Arduino pin connected to Blue Data 14 DS / SI of 74HC595

//=== B I T M A P ===
//Bits in this array represents one LED of the matrix
// 8 is # of rows, 7 is # of LED matrix we have
byte bitmap[8][7]; // Change the 7 to however many matrices you want to use.
int numZones = sizeof(bitmap) / 8; // I will refer to each group of 8 columns (represented by one matrix) as a Zone.
int maxZoneIndex = numZones-1;
int numCols = numZones * 8;

//=== F O N T ===
// Font courtesy of aspro648
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1203747843/22
// First char is @, next is A, B, etc.  Only lower case, no symbols.  
// The @ will display as space character.
byte alphabets[][5] = {
  {0,0,0,0,0},
  {31, 36, 68, 36, 31},
  {127, 73, 73, 73, 54},
  {62, 65, 65, 65, 34},
  {127, 65, 65, 34, 28},
  {127, 73, 73, 65, 65},
  {127, 72, 72, 72, 64},
  {62, 65, 65, 69, 38},
  {127, 8, 8, 8, 127},
  {0, 65, 127, 65, 0},
  {2, 1, 1, 1, 126},
  {127, 8, 20, 34, 65},
  {127, 1, 1, 1, 1},
  {127, 32, 16, 32, 127},
  {127, 32, 16, 8, 127},
  {62, 65, 65, 65, 62},
  {127, 72, 72, 72, 48},
  {62, 65, 69, 66, 61},
  {127, 72, 76, 74, 49},
  {50, 73, 73, 73, 38},
  {64, 64, 127, 64, 64},
  {126, 1, 1, 1, 126},
  {124, 2, 1, 2, 124},
  {126, 1, 6, 1, 126},
  {99, 20, 8, 20, 99},
  {96, 16, 15, 16, 96},
  {67, 69, 73, 81, 97},
};

//=== S E T U P ===

void setup() {
  pinMode(latchPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);

  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  
  //-- Clear bitmap --
  for (int row = 0; row < 8; row++) {
    for (int zone = 0; zone <= maxZoneIndex; zone++) {
      bitmap[row][zone] = 0; 
    }
  }
}

//=== F U N C T I O N S ===

// This routine takes whatever we've setup in the bitmap array and display it on the matrix
void RefreshDisplay()
{
  for (int row = 0; row < 8; row++) {
    int rowbit = 1 << row;
    digitalWrite(latchPin2, LOW);  //Hold latchPin LOW for as long as we're transmitting data
    shiftOut(dataPin2, clockPin2, MSBFIRST, rowbit);   //Transmit data

    //-- Start sending column bytes -- 
    digitalWrite(latchPin1, LOW);  //Hold latchPin LOW for as long as we're transmitting data

    //-- Shift out to each matrix (zone is 8 columns represented by one matrix)
    for (int zone = maxZoneIndex; zone >= 0; zone--) {
      shiftOut(dataPin1, clockPin1, MSBFIRST, bitmap[row][zone]);
    }

    //-- Done sending Column bytes, flip both latches at once to eliminate flicker
    digitalWrite(latchPin1, HIGH);  //Return the latch pin high to signal chip that it no longer needs to listen for information
    digitalWrite(latchPin2, HIGH);  //Return the latch pin high to signal chip that it no longer needs to listen for information

    //-- Wait a little bit to let humans see what we've pushed out onto the matrix --
    delayMicroseconds(500);
  }
}

// Converts row and colum to actual bitmap bit and turn it off/on
void Plot(int col, int row, bool isOn)
{
  int zone = col / 8;
  int colBitIndex = col % 8;
  byte colBit = 1 << colBitIndex;
  if (isOn)
    bitmap[row][zone] =  bitmap[row][zone] | colBit;
  else
    bitmap[row][zone] =  bitmap[row][zone] & (~colBit);
}

// Plot each character of the message one column at a time, updated the display, shift bitmap left.
void AlphabetSoup()
{
  char msg[] = "THE OBLIGATORY ARDUINO LED MATRIX PROJECT  ";

  for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
  {
    int alphabetIndex = msg[charIndex] - '@';
    if (alphabetIndex < 0) alphabetIndex=0;
    
    //-- Draw one character of the message --
    // Each character is only 5 columns wide, but I loop two more times to create 2 pixel space betwen characters
    for (int col = 0; col < 7; col++)
    {
      for (int row = 0; row < 8; row++)
      {
        // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
        bool isOn = 0; 
        if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
        Plot( numCols-1, row, isOn); // We ALWAYS draw on the rightmost column, the shift loop below will scroll it leftward.
      }
      
      //-- The more times you repeat this loop, the slower we would scroll --
      for (int refreshCount=0; refreshCount < 10; refreshCount++)
        RefreshDisplay();

      //-- Shift the bitmap one column to left --
      for (int row=0; row<8; row++)
      {
        for (int zone=0; zone < numZones; zone++)
        {
          // This right shift would show as a left scroll on display because leftmost column is represented by least significant bit of the byte.
          bitmap[row][zone] = bitmap[row][zone] >> 1;
          
          // Roll over lowest bit from the next zone as highest bit of this zone.
          if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7, bitRead(bitmap[row][zone+1],0));
        }
      }
    }
  }
}

//=== L O O P ===

void loop() {
  AlphabetSoup();
}
