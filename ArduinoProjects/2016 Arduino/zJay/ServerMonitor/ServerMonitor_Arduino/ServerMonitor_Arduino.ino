// Server Monitor Arduino Sketch
// For Jay by Hari Wiguna, 2016
//
// Instructions:
// 1. DHT should be on Arduino D2 (don't forget the 10K pullup resistor)
// 2. PC power switch should be on Arduino D3
// 3. PC reboot switch should be on Arduino D4.
// 4. Enter the MAC address printed on the bottom of shield to line marked with:
//    <--- UPDATE THIS FOR EACH ETHERNET SHIELD!!!
// 5. Upload the sketch
// 6. Open Serial Monitor to find out the IP Address assigned by your Access Point.
// 7. Use Notepad to enter IP Addresses in "ServerMonitor.exe.config"
//    BE CAREFUL NOT TO CHANGE ANYTHING ELSE !!!
// 8. Repeat steps 4-5 for each Arduino

/*
  Web Server

  A simple web server that shows the value of the analog input pins.
  using an Arduino Wiznet Ethernet shield.

  Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13
   Analog inputs attached to pins A0 through A5 (optional)

  created 18 Dec 2009
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe
  modified 02 Sept 2015
  by Arturo Guadalupi

*/

//--- DHT SENSOR ---
#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  
//#define DHTTYPE DHT21   // DHT 21 
DHT dht(DHTPIN, DHTTYPE);

//--- ETHERNET ---
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x00, 0x17, 0xD7 // <-- UPDATE THIS FOR EACH ETHERNET SHIELD!!!
};
// IPAddress ip(192, 168, 0, 0); // (NOT USED)

int powerPin = 3;
int resetPin = 4;

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
String line;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(powerPin, OUTPUT);
  pinMode(resetPin, OUTPUT);

  dht.begin();
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac);    //WAS: Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        line += c;
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {

//          char buffer[10];
//          Serial.write("\n");
//          Serial.write("[");
//          line.toCharArray(buffer, 10);
//          Serial.write(buffer);
//          Serial.write("]\n");

          //GET /P
          //0123456789
          if (line.length() >= 5)
          {
            if (line.charAt(5) == 'P')
            {
              Serial.write("*** Power");
              BlinkPin(powerPin);
            }
            if (line.charAt(5) == 'R')
            {
              Serial.write("*** Reset");
              BlinkPin(resetPin);
            }
            Serial.write("\n");
          }

          line = "";

          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          float f = dht.readTemperature(true);
          client.print(f);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    Ethernet.maintain();
  }
}

void BlinkPin(int pinNumber)
{
  digitalWrite(pinNumber, HIGH);
  delay(1000);
  digitalWrite(pinNumber, LOW);
}

