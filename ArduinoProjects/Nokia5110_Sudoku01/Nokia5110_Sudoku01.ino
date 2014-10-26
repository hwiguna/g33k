//
// Hari Suduino, Oct 2014
// Huge thank you to AdaFruit for the libraries!

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!


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

void loop() {
  ScanKeypad();
  RefreshCursor();
}




