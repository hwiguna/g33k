/* SPI  S L A V E
 * by Hari Wiguna
 * With huge thanks to Nick Gammon and Roger Linhart
 *
 * v00 - one byte command
 * v01 - Master sends 0, 1, 2, ..7
 *
 * SPI pin numbers:
 * SCK   13  // Serial Clock.
 * MISO  12  // Master In Slave Out.
 * MOSI  11  // Master Out Slave In.
 * SS    10  // Slave Select
 */

#include <SPI.h>

const int ON = HIGH;
const int OFF = LOW;
const int SELECTED = LOW; // Master brings SS pin low to indicate that we're THE slave.

boolean isActiveSlave = false;// Do we currently own the MISO line (Master-In, SlaveOut)
const byte ledPin = 8;        // Slave LED digital I/O pin.
boolean ledState = OFF;      // LED state flag.
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
  if (digitalRead(SS) == SELECTED) { // Are we the slave chosen by Master?
    if (!isActiveSlave) { // have we claimed MISO line yet?
      pinMode(MISO, OUTPUT);// Yes, take MISO pin. Master-In, Slave-Out.
      Serial.println("\n[[[ Slave Enabled.");
      isActiveSlave = true;
    }

    rx = SPItransfer(255); // Send garbage (we don't know what master wants) and receive master command code
    Serial.println("Initial garbage slave response code sent");
    Serial.println("rx:" + String(rx) + ".");
    if (rx != -1 && rx >= 0 && rx < 8)
    {
      Serial.println("Data received from master: " + String(rx));
      rx = SPItransfer(rx);// Acknowledge data
      Serial.println("Acknowledge received data. Master" );
      Serial.println("rx:" + String(rx) + ".");
      ledState = !ledState; // Toggle LED State
      digitalWrite(ledPin, ledState);
    }
    else
    {
      rx = SPItransfer(255);// Unrecognized command.
      Serial.println("** Unrecognized Command -1 slave response code sent.");
      Serial.println("rx:" + String(rx) + ".");
    }
  }
  else {
    // Master deselects us as slave, we need to release MISO line if we have it
    if (isActiveSlave) {
      pinMode(MISO, INPUT);// Yes, release MISO pin. Let another Slave talk to Master.
      Serial.println("Slave Disabled ]]]");
      isActiveSlave = false; // We're no longer an active slave
    }
  }
}

