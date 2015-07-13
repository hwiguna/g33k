/* SPI  S L A V E - originally by Roger Linhart and Nick Gammon
 *
 * Slave toggles slave LED upon receipt of buttonPressedCommand code.
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
const byte readLEDCommand = 2;        // Master command read slave LED state.

boolean isActiveSlave = false;// Do we currently own the MISO line (Master-In, SlaveOut)
const byte ledPin = 8;        // Slave LED digital I/O pin.
boolean ledState = HIGH;      // LED state flag.
byte rx;

void SlaveInit(void) {
  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, INPUT);
  pinMode(SS, INPUT);
  SPCR = (1 << SPE);// Enable SPI as slave.
}

byte SPItransfer(byte value) {
  SPDR = value;
  while (!(SPSR & (1 << SPIF)));
  delay(10);
  return SPDR;
}

void setup() {
  Serial.begin(9600);// Initialize serial for troubleshooting.
  pinMode(ledPin, OUTPUT);// Initialize slave LED pin.
  digitalWrite(ledPin, ledState);
  SlaveInit();
  Serial.println("Slave Initialized");
}

void loop() {
  if (digitalRead(SS) == LOW) { // Slave Enabled? LOW = Enabled
    if (!isActiveSlave) { // have we claimed MISO line yet?
      pinMode(MISO, OUTPUT);// Yes, take MISO pin. Master-In, Slave-Out.
      Serial.println("***Slave Enabled.");
      isActiveSlave = true;
    }
    // Write -1 slave response code and receive master command code
    rx = SPItransfer(255);
    Serial.println("Initial -1 slave response code sent");
    Serial.println("rx:" + String(rx) + ".");
    switch (rx)
    {
      case buttonPressedCommand: // buttonPressedCommand?
        rx = SPItransfer(buttonPressedCommand);// Acknowledge buttonPressedCommand.
        Serial.println("buttonPressedCommand Acknowledged.");
        Serial.println("rx:" + String(rx) + ".");
        ledState = !ledState; // Toggle LED State
        digitalWrite(ledPin, ledState);
        break;

      case readLEDCommand: // buttonPressedCommand?
        rx = SPItransfer(readLEDCommand);// Acknowledge readLEDCommand.
        Serial.println("readLEDCommand Acknowledged.");
        Serial.println("rx:" + String(rx) + ".");
        rx = SPItransfer(ledState);
        Serial.println("ledState:" + String(ledState) + " Sent.");
        Serial.println("rx:" + String(rx) + ".");
        break;

      default: // Unrecognized command.
        rx = SPItransfer(255);// Unrecognized command.
        Serial.println("Unrecognized Command -1 slave response code sent.");
        Serial.println("rx:" + String(rx) + ".");
        break;
    }
  }
  else {
    // Master deselects us as slave, we need to release MISO line if we have it
    if (isActiveSlave) {
      pinMode(MISO, INPUT);// Yes, release MISO pin. Let another Slave talk to Master.
      Serial.println("Slave Disabled.");
      isActiveSlave = false; // We're no longer an active slave
    }
  }
}

