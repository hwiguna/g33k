// ATTiny84 8x8 Matrix - ANODE Rows
/* SPI  S L A V E
 * by Hari Wiguna
 * Big thanks to Nick Gammon, Jack Christensen, and Roger Linhart
 *
 * v00 - one byte command
 * v01 - Master sends 0, 1, 2, ..7
 * v02 - ATTiny version!
 * v03 - Take out SS, always assume one ATTiny is master, the otther slave.
 * v04 - bit bang SPI slave
 * 
 * SPI pin numbers:
 * SCK   13  // Serial Clock.
 * MISO  12  // Master In Slave Out.
 * MOSI  11  // Master Out Slave In.
 * SS    10  // Slave Select (UNUSED!!!)
 */
const int SCK = 4;
const int MOSI = 6;
const int MISO = 5; 

const int SELECTED = LOW; // Master brings SS pin low to indicate that we're THE slave.
boolean isActiveSlave = false;// Do we currently own the MISO line (Master-In, SlaveOut)
byte rx;

//=== Row Variables ==
int anodePins[8] = {0, 1, 2, 3, 7, 8, 9, 10};
int pinIndex = 0;
const int ON = HIGH;
const int OFF = LOW;

void setup() {
  // Initialize SPI pins as slave pins!
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT); // Master-Out, Slave-In.  We're Slave, we listen to this line.
  pinMode(MISO, OUTPUT);// Master-In, Slave-Out. We're Slave, we talk on this line.

  //-- Row pins init --
  for (int i = 0; i < 8; i++)
  {
    pinMode(anodePins[i], OUTPUT);
    digitalWrite(anodePins[pinIndex], OFF);
  }

}

void loop() {
  int sck = digitalRead(SCK);
  int mosi = digitalRead(MOSI);

  digitalWrite(0,sck);
  digitalWrite(1,mosi);
}

