// 3 minute IoT - Download from Cloud
// Hari Wiguna, 2015

// Libraries - Thanks AdaFruit!
#include <ESP8266WiFi.h>
#include "Adafruit_IO_Client.h"

// Configure WiFi access point & AdaFruit.io account.
#define WLAN_SSID  "Firefly24"
#define WLAN_PASS  "??????????"
#define ADAFRUIT_IO_KEY    "??????????"

// Create an ESP8266 WiFiClient, AdaFruit.io client, and our lightFeed
WiFiClient client;
Adafruit_IO_Client aio = Adafruit_IO_Client(client, ADAFRUIT_IO_KEY);
Adafruit_IO_Feed lightFeed = aio.getFeed("light");

byte ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);

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

  aio.begin();

  Serial.println(F("Ready!"));
}

void loop() {
  //--- READ LIGHT FEED STATE ---
  FeedData feedData = lightFeed.receive();
  if (feedData.isValid()) {
    Serial.print(F("Received value from feed: ")); Serial.println(feedData);
    digitalWrite(ledPin, strcmp(feedData,"ON"));
  }
  else {
    Serial.print(F("Failed to receive the latest feed value!"));
  }

  // Don't be a jerk and abuse AdaFruit.io.  Wait a second in-between data requests.
  delay(1000);
}
