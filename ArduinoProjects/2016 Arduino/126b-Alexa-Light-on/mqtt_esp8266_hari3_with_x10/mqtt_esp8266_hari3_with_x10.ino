// Amazon Echo meets X-10
// Hari Wiguna, 2016
//
// Hacked together from:
// - Adafruit MQTT Library ESP8266 Example
// - and http://playground.arduino.cc/X10/CM17A

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <X10Firecracker.h> // Use the modified version of this that no longer rely on ATMega specific features. -- Hari

// Configurations
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "?????"
#define WLAN_SSID  "Firefly24"
#define WLAN_PASS  "?????"
#define AIO_KEY    "?????"

int ledPin = 2;
bool isDebug = false; // Don't debug if USB serial is not connected

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Store the MQTT server, username, and password in flash memory.
// This is required for using the Adafruit MQTT library.
const char MQTT_SERVER[] PROGMEM    = AIO_SERVER;
const char MQTT_USERNAME[] PROGMEM  = AIO_USERNAME;
const char MQTT_PASSWORD[] PROGMEM  = AIO_KEY;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, AIO_SERVERPORT, MQTT_USERNAME, MQTT_PASSWORD);

/****************************** Feeds ***************************************/
// Setup a feed called 'light' for subscribing to changes.
const char ONOFF_FEED[] PROGMEM = AIO_USERNAME "/feeds/light";
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, ONOFF_FEED);

/*************************** Sketch Code ************************************/

void setup() {
  X10.init( 0, 2, 5 ); // 0=RTS, 2=DTR, 5=extra delay for faster ESP8266

  if (isDebug) Serial.begin(115200);
  delay(10);

  if (isDebug)
  {
    Serial.println(F("Adafruit MQTT demo"));

    // Connect to WiFi access point.
    Serial.println(); Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);
  }

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (isDebug) Serial.print(".");
  }
  
  if (isDebug)
  {
    Serial.println();

    Serial.println("WiFi connected");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());
  }

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  if (isDebug) Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    if (isDebug) {
      Serial.println(mqtt.connectErrorString(ret));

      Serial.println("Retrying MQTT connection in 5 seconds...");
    }
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
  }
  if (isDebug) Serial.println("MQTT Connected!");
}
void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(3000))) {
    if (subscription == &onoffbutton) {
      if (isDebug) {
        Serial.print(F("Got: "));
        Serial.println((char *)onoffbutton.lastread);
      }

      if (strcmp((char*)onoffbutton.lastread, "OFF") == 0) {
        X10.sendCmd( hcA, 1, cmdOff );
        //digitalWrite(ledPin, HIGH);
      }
      if (strcmp((char*)onoffbutton.lastread, "ON") == 0) {

        X10.sendCmd( hcA, 1, cmdOn );
        //digitalWrite(ledPin, LOW);
      }
    }
  }

  // I find it more reliable to let mqtt timeout and reconnect. ping flushes buffer causing packet loss -- Hari
  // ping the server to keep the mqtt connection alive
  //if (! mqtt.ping()) {
  //  mqtt.disconnect();
  //}
  //delay(1000);
}

