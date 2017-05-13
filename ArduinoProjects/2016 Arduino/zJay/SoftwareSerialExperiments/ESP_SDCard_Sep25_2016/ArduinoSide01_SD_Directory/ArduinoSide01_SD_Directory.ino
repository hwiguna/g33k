/*
  Software serial multple serial test

  Receives from the hardware serial, sends to software serial.
  Receives from software serial, sends to hardware serial.

  The circuit:
   RX is digital pin 10 (connect to TX of other device)
   TX is digital pin 11 (connect to RX of other device)

  Note:
  Not all pins on the Mega and Mega 2560 support change interrupts,
  so only the following can be used for RX:
  10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

  Not all pins on the Leonardo support change interrupts,
  so only the following can be used for RX:
  8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

  created back in the mists of time
  modified 25 May 2012
  by Tom Igoe
  based on Mikal Hart's example

  This example code is in the public domain.

*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 8); // RX=9, TX=8 // 10,9 does not work

// The circuit:
// * SD card attached to SPI bus as follows:
// ** MOSI - pin 11
// ** MISO - pin 12
// ** CLK - pin 13
// ** CS - pin 4
#include <SPI.h>
#include <SD.h>

File root;

String inputString = "";         // a string to hold incoming data
const int bufLen = 500;
char buf[bufLen];

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);
  mySerial.println("Hello, world?");


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  mySerial.println("initialization done.");
}

void printDirectory(File dir, int numTabs) {
  
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      mySerial.print("&nbsp;&nbsp;");
      Serial.print('\t');
    }
    mySerial.print(entry.name());
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      mySerial.println("/<br/>");
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      mySerial.println("<br/>");
      Serial.println();
    }
    entry.close();
  }
}

void loop() { // run over and over
  if (mySerial.available()) {
    //Serial.write(mySerial.read());

    char inChar = (char)mySerial.read();
    // add it to the inputString:j
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {

      mySerial.println("Directory:");
      //      inputString.toCharArray(buf, bufLen);
      //      mySerial.write(buf, inputString.length());
      //
      
      root = SD.open("/");
      printDirectory(root, 0);
      root.close();

      mySerial.print("$");

      //inputString = "";
    }
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

