// 3 minute IoT - Download from Cloud (AdaFruit.io)
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
Adafruit_IO_Feed testFeed = aio.getFeed("onoff");

void setup() {
  pinMode(2, OUTPUT);

  Serial.begin(115200);
  delay(10);
  Serial.println(); Serial.println();
  Serial.println(F("3 minute IoT - Download from Cloud"));

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

  Serial.println(F("Ready!"));
}

void loop() {
  // To read the latest feed value call the receive function on the feed.
  // The returned object will be a FeedData instance and you can check if it's
  // valid (i.e. was successfully read) by calling isValid(), and then get the
  // value either as a text value, or converted to an int, float, etc.
  FeedData latest = testFeed.receive();
  if (latest.isValid()) {
    Serial.print(F("Received value from feed: ")); Serial.println(latest);
    // By default the received feed data item has a string value, however you
    // can use the following functions to attempt to convert it to a numeric
    // value like an int or float.  Each function returns a boolean that indicates
    // if the conversion succeeded, and takes as a parameter by reference the
    // output value.
    int i;
    if (latest.intValue(&i)) {
      Serial.print(F("Value as an int: ")); Serial.println(i, DEC);
      digitalWrite(2, i == 1 ? LOW : HIGH); // bring pin 2 low to turn on LED.
    }
    // Other functions that you can use include:
    //  latest.uintValue() (unsigned int)
    //  latest.longValue() (long)
    //  latest.ulongValue() (unsigned long)
    //  latest.floatValue() (float)
    //  latest.doubleValue() (double)
  }
  else {
    Serial.print(F("Failed to receive the latest feed value!"));
  }

  // Don't be a jerk and abuse AdaFruit.io.  Wait a second in-between data requests.
  delay(1000);
}
