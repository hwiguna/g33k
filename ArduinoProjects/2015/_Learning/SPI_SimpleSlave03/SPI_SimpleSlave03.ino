// ATTiny84 8x8 Matrix - ANODE Rows
/* SPI  S L A V E
 * by Hari Wiguna
 * Big thanks to Nick Gammon, Jack Christensen, and Roger Linhart
 *
 * v00 - one byte command
 * v01 - Master sends 0, 1, 2, ..7
 * v02 - ATTiny version!
 * v03 - Take out SS, always assume one ATTiny is master, the otther slave.
 *
 * SPI pin numbers:
 * SCK   13  // Serial Clock.
 * MISO  12  // Master In Slave Out.
 * MOSI  11  // Master Out Slave In.
 * SS    10  // Slave Select (UNUSED!!!)
 */

//#include <SPI.h>

//#include <avr/io.h> // for SPCR, SPE, SPDR, SPIF
#include <tinySPI.h>               //http://github.com/JChristensen/tinySPI
//const int SS = 10;    // tinySPI.h does not define this
const int SCK = USCK_DD_PIN; // Translate tinySPI's pin notations to standard SPI notations
const int MOSI = DO_DD_PIN; // PA5
const int MISO = DI_DD_PIN; // PA6 
#define SPDR USIDR
#define SPSR USISR
#define SPIF USIOIF

const int SELECTED = LOW; // Master brings SS pin low to indicate that we're THE slave.
boolean isActiveSlave = false;// Do we currently own the MISO line (Master-In, SlaveOut)
byte rx;

//=== Row Variables ==
int anodePins[8] = {0, 1, 2, 3, 7, 8, 9, 10};
int pinIndex = 0;
const int ON = HIGH;
const int OFF = LOW;

void SlaveInit(void) {
  SPI.begin(); // TinySPI does not support Slave mode, so init as master first.
  
  // RE-initialize SPI pins as slave pins!
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, INPUT);
  //pinMode(SS, INPUT);
  ///SPCR = (1 << SPE);// Enable SPI as slave.
}

byte SPItransfer(byte value) {
  SPDR = value;
  while (!(SPSR & (1 << SPIF)));
  delay(10);
  return SPDR;
}

void setup() {
  //Serial.begin(9600);// Initialize serial for troubleshooting.
  //pinMode(ledPin, OUTPUT);// Initialize slave LED pin.
  //digitalWrite(ledPin, ledState);
  SlaveInit();
  //Serial.println("Slave Initialized");

  //-- Row pins init --
  for (int i = 0; i < 8; i++)
  {
    pinMode(anodePins[i], OUTPUT);
    digitalWrite(anodePins[pinIndex], OFF);
  }

  pinMode(MISO, OUTPUT);// Yes, take MISO pin. Master-In, Slave-Out.
}

void loop() {
  //rx = SPItransfer(255); // Send garbage (we don't know what master wants) and receive master command code
  rx = SPDR;
  SPDR = 255;
  while (!(SPSR & (1 << SPIF)));
  delay(10);
  //Serial.println("Initial garbage slave response code sent");
  //Serial.println("rx:" + String(rx) + ".");
  if (rx != -1 && rx >= 0 && rx < 8)
  {
    //Serial.println("Data received from master: " + String(rx));
    //SPItransfer(rx);// Acknowledge data
    //rx = SPDR;
//  SPDR = rx;
//  while (!(SPSR & (1 << SPIF)));
//  delay(10);
    for (int r = 0; r < 8; r++)
      digitalWrite(anodePins[pinIndex], (rx == r) ? ON : OFF);
  }
//  else
//  {
//    rx = SPItransfer(255);// Unrecognized command.
//    //Serial.println("** Unrecognized Command -1 slave response code sent.");
//    //Serial.println("rx:" + String(rx) + ".");
//  }
}

