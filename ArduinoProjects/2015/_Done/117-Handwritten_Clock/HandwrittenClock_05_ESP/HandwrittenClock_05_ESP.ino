// Handwritten Clock
// This the Master code running on the ESP8266
// Hari Wiguna, 2015
// Started with NTPClient sample by Michael Margolis, Tom Igoe, Grokhotkov

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//-- Preferences --
char ssid[] = "Firefly24";  //  your network SSID (name)
char pass[] = "---";       // your network password
int timeZone = -5;
int getTimeEveryXmillis = 5 * 1000; // every 10 seconds

unsigned long timeToGetTime;
unsigned long gEpoch;

unsigned int localPort = 2390;      // local port to listen for UDP packets

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup()
{
  //-- Open Serial port to Arduino --
  Serial.begin(115200);
  Serial.println("Hi");

  //-- Connect to WiFi network --
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("WiFi");

  //-- Start UDP --
  udp.begin(localPort);
  Serial.println("Ready!");
}

void loop()
{
  if (millis() > timeToGetTime) {
    GetTimeFromInternet();
    timeToGetTime = millis() + getTimeEveryXmillis;
  }
}

void GetTimeFromInternet()
{
  //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP);

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);

  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("Fail");
  }
  else {
    //Serial.print("OK ");
    //Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;

    // now convert NTP time into everyday time:
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    gEpoch = secsSince1900 - seventyYears;

    //-- Send Epoch to Arduino --
    Serial.print("#");
    //Serial.println(gEpoch);
  
    //    byte hh = (epoch  % 86400L) / 3600;
    //    byte mm = (epoch  % 3600) / 60;
    //    byte ss = epoch % 60;
  }
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  ///Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}
