/* SPI  M A S T E R - originally by Roger Linhart and Nick Gammon
 *  v00 - one byte command
 *
 * Master monitors master button and sends button press status to slave
 * Master reads slave LED status every 5 seconds and updates master LED status.
 *
 * Communication Protocol:
 * Slave acknowledges SS (Slave Select) by sending -1 slave response code and
 * receiving master command code. On subsequent SS slave echoes master command
 * code or -1 slave response code indicating an unrecognized command has been
 * received. Additional SS's may be needed to transfer additional data to/from
 * Slave depending on the master command code.
 * Master command code: buttonPressedCommand = Inform slave of a master button press.
 *
 * SPI pin numbers:
 * SCK   13  // Serial Clock.
 * MISO  12  // Master In Slave Out.
 * MOSI  11  // Master Out Slave In.
 * SS    10  // Slave Select
 */

#include <SPI.h>

const byte buttonPressedCommand = 1;  // Master command button press.
//const byte slaveResponse = 255; // What slave would return to acknowledge received command
const byte buttonPin = 9;        // Master button digital I/O pin.
const byte ledPin = 8;        // Slave LED digital I/O pin.

const int PRESSED = LOW; // buttonPin is normalled pulled up high by internal resistor.

void setup() {
  Serial.begin(9600);// Initialize serial for troubleshooting.
  pinMode(buttonPin, INPUT_PULLUP);// Initialize master button.
  pinMode(ledPin, OUTPUT);// Initialize master led.

  // Initialize SPI.
  // SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();

  //SPI.setClockDivider(SPI_CLOCK_DIV8);  // Slow down the master a bit
  Serial.println("Master Initialized");
}

void loop() {
  if (digitalRead(buttonPin)==PRESSED) {// Master button pressed?
    Serial.println("Master Button Pressed.");

    digitalWrite(SS, LOW); // Select and wait for slave.  LOW = Select Slave
    Serial.println("***Slave Selected.");
    delay(20); // Give slave time to check his Slave Select pin

    SPI.transfer(buttonPressedCommand); // Send buttonPressedCommand, ignore meaningless slave response (it didn't know what master wants)
    Serial.println("buttonPressedCommand Sent.");
    delay(20);// Wait for slave.

    byte rx = SPI.transfer(0); // Send garbage, Get slave response.
    switch (rx)
    {
      case buttonPressedCommand: // Acknowledged?
        Serial.println("Slave acknowledged buttonPressedCommand.");
        break;

      case 255: // Command not recognized?
        Serial.println("Slave returned -1 slave return code - master command code not recognized.");
        break;

      default: // Unrecognized response.
        Serial.println("Slave returned:" + String(rx) + ".");
        break;
    }

    digitalWrite(SS, HIGH); // Disable slave.
    delay(500); // Debounce master button.
  }
}

