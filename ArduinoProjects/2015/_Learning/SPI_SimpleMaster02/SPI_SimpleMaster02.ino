// ATTiny84 8x8 Matrix - GREEN columns
/* SPI  M A S T E R
 * by Hari Wiguna
 * With huge thanks to Nick Gammon, Jack Christensen, and Roger Linhart
 *
 * v00 - one byte command
 * v01 - Master sends 0, 1, 2, ..7
 * v02 - ATTiny version!
 *
 * SPI pin numbers:
 * SCK   13  // Serial Clock.
 * MISO  12  // Master In Slave Out.
 * MOSI  11  // Master Out Slave In.
 * SS    10  // Slave Select
 */

//#include <SPI.h>
#include <tinySPI.h>               //http://github.com/JChristensen/tinySPI
const int SS = 10; // tinySPI.h does not define this

//== Column variables ==
const int ON = LOW;
const int OFF = HIGH;
int dly = 60;
int colPins[8] = {10, 9, 8, 7, 3, 2, 1, 0};

void setup() {
  //Serial.begin(9600);// Initialize serial for troubleshooting.
  //pinMode(ledPin, OUTPUT);// Initialize master led.

  // Initialize SPI.
  // SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();

  //SPI.setClockDivider(SPI_CLOCK_DIV8);  // Slow down the master a bit
  //Serial.println("Master Initialized");

  //-- Init column pins --
  for (int i = 0; i < 8; i++)
  {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], OFF);
  }
}

void loop() {

  for (int r = 0; r < 8; r++)
  {
    SPISend(r);
    for (int c = 0; c < 8; c++)
    {
      digitalWrite(colPins[c], ON);
      delay(dly);
      digitalWrite(colPins[c], OFF);
    }
  }
}

void SPISend(byte data)
{
  digitalWrite(SS, LOW); // Select and wait for slave.  LOW = Select Slave
  //Serial.println("\n[[[ Slave Selected.");
  delay(20); // Give slave time to check his Slave Select pin

  SPI.transfer(data); // Send data, ignore meaningless slave response (it didn't know what master wants)
  //Serial.print(data, DEC);
  //Serial.println(" sent.");
  delay(20);// Wait for slave.

  byte rx = SPI.transfer(255); // Send garbage, Get slave response.
  if (rx >= 0 && rx < 8)
  {
    //Serial.print("Slave acknowledged: ");
    //Serial.println(rx, DEC);
  }
  else
  {
    //Serial.println("Master does not expect that slave returned:" + String(rx) + ".");
  }
  digitalWrite(SS, HIGH); // Disable slave.
  //Serial.println("Slave UNSELECTED ]]]");
  //delay(500); // Debounce master button.
}

