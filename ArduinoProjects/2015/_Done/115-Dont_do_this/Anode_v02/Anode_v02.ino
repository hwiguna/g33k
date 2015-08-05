// ATTiny84 8x8 Matrix - ANODE Rows

v2 - Adding *SPI SLAVE* to listen for signal to switch row

//=== SPI ===
#include <SPI.h>
const int slaveSelectPin = 10;
char buf [100];
volatile byte pos;
volatile boolean process_it;

//=== Row Variables ==
int anodePins[8] = {0, 1, 2, 3, 7, 8, 9, 10};
int pinIndex = 0;
const int ON = HIGH;
const int OFF = LOW;


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin (115200);   // debugging
  
  //-- SPI --
  pinMode (slaveSelectPin, OUTPUT); // set the slaveSelectPin as an output
  SPI.begin(); // initialize SPI

  //-- Row pins init --
  for (int i = 0; i < 8; i++)
  {
    pinMode(anodePins[i], OUTPUT);
    digitalWrite(anodePins[pinIndex], OFF);
  }
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(anodePins[pinIndex], ON);
  delay(1000);
  digitalWrite(anodePins[pinIndex], OFF);
  pinIndex++;
  if (pinIndex > 7) pinIndex = 0;
}
