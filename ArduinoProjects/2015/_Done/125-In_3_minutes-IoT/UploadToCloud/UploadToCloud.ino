// 3 minute IoT - Upload to Cloud (AdaFruit.io)
// Hari Wiguna, 2015
// Hacked from examples by AdaFruit.

// Adafruit IO REST API access with ESP8266
//
// For use with ESP8266 Arduino from:
//   https://github.com/esp8266/Arduino
//
// Works great with ESP8266 modules like the Adafruit Huzzah ESP:
//  ----> https://www.adafruit.com/product/2471
//
// Written by Tony DiCola for Adafruit Industries.
// MIT license, all text above must be included in any redistribution.

#include <ESP8266WiFi.h>
#include "Adafruit_IO_Client.h"

// Configure WiFi access point details.
#define WLAN_SSID  "Winternet"
#define WLAN_PASS  "neffistu"

// Configure Adafruit IO access.
#define AIO_KEY    "a812b5a6e55b471c00c9af222bd4ea82382403e6"

// Create an ESP8266 WiFiClient class to connect to the AIO server.
WiFiClient client;

// Create an Adafruit IO Client instance.  Notice that this needs to take a
// WiFiClient object as the first parameter, and as the second parameter a
// default Adafruit IO key to use when accessing feeds (however each feed can
// override this default key value if required, see further below).
Adafruit_IO_Client aio = Adafruit_IO_Client(client, AIO_KEY);

// Finally create instances of Adafruit_IO_Feed objects, one per feed.  Do this
// by calling the getFeed function on the Adafruit_IO_FONA object and passing
// it at least the name of the feed, and optionally a specific AIO key to use
// when accessing the feed (the default is to use the key set on the
// Adafruit_IO_Client class).
Adafruit_IO_Feed temperatureFeed = aio.getFeed("Temperature");
Adafruit_IO_Feed humidityFeed = aio.getFeed("Humidity");


//--------------- SENSOR -----------------------------
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
//----------------------------------------------------

void setup() {
  pinMode(2, OUTPUT);

  Serial.begin(115200);
  delay(10);
  Serial.println(); Serial.println();
  Serial.println(F("3 minute IoT - Upload to Cloud"));

  // Connect to WiFi access point.
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Initialize the Adafruit IO client class (not strictly necessary with the
  // client class, but good practice).
  aio.begin();

  //--- SENSOR ---
  dht.begin();

  Serial.println(F("Ready!"));
}

void loop() {

  //--- READ AND SEND TEMPERATURE ---
  int f = dht.readTemperature(true);
  Serial.print(F("Temperature = ")); Serial.println(f, DEC);
  if (!temperatureFeed.send(f)) Serial.println(F("*** Error writing value to temperatureFeed!"));

  //--- READ AND SEND HUMIDITY ---
  int h = dht.readHumidity();
  Serial.print(F("Humidity = ")); Serial.println(h, DEC);
  if (!humidityFeed.send(h))Serial.println(F("*** Error writing value to humidityFeed!"));

  //delay(1000); // No need for delay, DHT sensor takes 2 seconds to gather data :-(
}
