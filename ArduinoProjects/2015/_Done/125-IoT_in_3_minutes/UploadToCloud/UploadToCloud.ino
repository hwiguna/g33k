// 3 minute IoT - Upload to Cloud
// Hari Wiguna, 2015

// Libraries - Thanks AdaFruit!
#include <ESP8266WiFi.h>
#include "Adafruit_IO_Client.h"

// Configure WiFi access point & AdaFruit.io account.
#define WLAN_SSID  "Firefly24"
#define WLAN_PASS  "??????????"
#define ADAFRUIT_IO_KEY    "??????????"

// Create an ESP8266 WiFiClient class to connect to the AIO server.
WiFiClient client;
Adafruit_IO_Client aio = Adafruit_IO_Client(client, ADAFRUIT_IO_KEY);
Adafruit_IO_Feed temperatureFeed = aio.getFeed("Temperature");
Adafruit_IO_Feed humidityFeed = aio.getFeed("Humidity");

//--------------- SENSOR -----------------------------
#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
//----------------------------------------------------

void setup() {
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
