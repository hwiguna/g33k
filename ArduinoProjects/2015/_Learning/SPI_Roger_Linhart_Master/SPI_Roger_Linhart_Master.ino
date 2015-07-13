/* SPI  M A S T E R - originally by Roger Linhart and Nick GammoN
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
const byte readLEDCommand = 2;        // Master command read slave LED state.

unsigned long nextMillis = 0;    // Next millis() for master LED update.
const byte buttonPin = 9;        // Master button digital I/O pin.
const byte ledPin = 8;           // Master LED digital I/O pin.

void setup() {
  Serial.begin(9600);// Initialize serial for troubleshooting.
  pinMode(buttonPin, INPUT_PULLUP);// Initialize master button.
  pinMode(ledPin, OUTPUT);// Initialize master led.
  nextMillis = millis();// Initialize nextMillis.

  // Initialize SPI.
  // SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();

  //SPI.setClockDivider(SPI_CLOCK_DIV8);  // Slow down the master a bit
  Serial.println("Master Initialized");
}

void loop() {
  if (digitalRead(buttonPin)==LOW) {// Master button pressed?
    Serial.println("Master Button Pressed.");

    digitalWrite(SS, LOW); // Select and wait for slave.  LOW = Select Slave
    Serial.println("***Slave Selected.");
    delay(20); // Give slave time to check his Slave Select pin

    // Send buttonPressedCommand
    SPI.transfer(buttonPressedCommand);
    Serial.println("buttonPressedCommand Sent.");
    delay(20);// Wait for slave.

    byte rx = SPI.transfer(255); // Get slave response.
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

/*
  if (millis() >= nextMillis) { // Time to update master LED?
    nextMillis = millis() + 5000;
    Serial.println("nextMillis Updated.");

    digitalWrite(SS, LOW);    // Select and wait for slave.
    Serial.println("***Slave Selected.");
    delay(20);

    // Send readLEDCommand.
    byte rx = SPI.transfer(readLEDCommand);
    Serial.println("readLEDCommand Sent.");
    Serial.println("rx:" + String(rx) + ".");
    delay(20);// Wait for slave.

    // Get slave response.
    rx = SPI.transfer(255);
    Serial.println("-1 slave return code Sent.");
    Serial.println("rx:" + String(rx) + ".");

    if (rx == readLEDCommand) {// Acknowledged?
      Serial.println("Slave acknowledged readLEDCommand.");

      delay(20);// Wait for slave.

      // Get Slave LED State.
      byte rx = SPI.transfer(255);
      Serial.println("-1 slave return code Sent.");
      Serial.println("rx=" + String(rx) + ".");
      Serial.println("Slave LED State:" + String(rx) + ".");

      // Update Master LED State.
      digitalWrite(ledPin, rx);
      Serial.println("Master LED State Updated.");
    }

    else if (rx == 255) {// Command not recognized?
      Serial.println("Slave returned -1 slave return code - master command code not recognized.");
    }

    else {// Unrecognized response.
      Serial.println("Slave returned:" + String(rx) + ".");
    }

    digitalWrite(SS, HIGH);// Disable slave.
  }
  */
}

