/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board:
  ----> https://www.adafruit.com/product/2471
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  Adafruit IO example additions by Todd Treece.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/****************************** Pins ******************************************/

//#define BUTTON          0   // NodeMCU d3
//#define LAMP            13  // NodeMCU d7
//#define PHOTOCELL       A0  // analog 0
#define BUTTON          0   // NodeMCU d3
#define LAMP            2  // NodeMCU d7
#define PHOTOCELL       A0  // analog 0

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Firefly24"
#define WLAN_PASS       "---"
//#define WLAN_SSID       "ng-guest"
//#define WLAN_PASS       "dontpanic"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "hwiguna"
#define AIO_KEY         "---"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Store the MQTT server, client ID, username, and password in flash memory.
// This is required for using the Adafruit MQTT library.
const char MQTT_SERVER[] PROGMEM    = AIO_SERVER;
// Set a unique MQTT client ID using the AIO key + the date and time the sketch
// was compiled (so this should be unique across multiple devices for a user,
// alternatively you can manually set this to a GUID or other random value).
const char MQTT_CLIENTID[] PROGMEM  = __TIME__ AIO_USERNAME;
const char MQTT_USERNAME[] PROGMEM  = AIO_USERNAME;
const char MQTT_PASSWORD[] PROGMEM  = AIO_KEY;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, AIO_SERVERPORT, MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);

/****************************** Feeds ***************************************/

// Setup a feed called 'button' for publishing changes.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
const char BUTTON_FEED[] PROGMEM = AIO_USERNAME "/feeds/button";
Adafruit_MQTT_Publish button = Adafruit_MQTT_Publish(&mqtt, BUTTON_FEED);

// Setup a feed called 'lamp' for subscribing to changes.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
const char LAMP_FEED[] PROGMEM = AIO_USERNAME "/feeds/lamp";
Adafruit_MQTT_Subscribe lamp = Adafruit_MQTT_Subscribe(&mqtt, LAMP_FEED);

// Setup a feed called 'photocell' for publishing changes.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
const char PHOTOCELL_FEED[] PROGMEM = AIO_USERNAME "/feeds/photocell";
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, PHOTOCELL_FEED);

/*************************** Sketch Code ************************************/

// button state
int current = 0;
int last = -1;
int currentA = 0;
int lastA = -1;
Adafruit_MQTT_Subscribe *subscription;

void setup() {

  // set button pin as an input
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LAMP, OUTPUT);

  Serial.begin(115200);

  Serial.println(F("Adafruit IO Example"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();

  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());

  // listen for events on the lamp feed
  mqtt.subscribe(&lamp);

  // connect to adafruit io
  connect();

  digitalWrite(LAMP, HIGH);
}

void loop() {
  // ping adafruit io a few times to make sure we remain connected
  if (! mqtt.ping(3)) {
    // reconnect to adafruit io
    if (! mqtt.connected())
      connect();
  }

  checkEvents();
  //publishPhotocell();
  publishButton();
}

void checkEvents()
{
  // this is our 'wait for incoming subscription packets' busy subloop
  //Serial.print(F("I?"));
  while (subscription = mqtt.readSubscription(1000)) {

    Serial.println(F("Incoming!"));
    // we only care about the lamp events
    if (subscription == &lamp) {

      // convert mqtt ascii payload to int
      char *value = (char *)lamp.lastread;
      Serial.print(F("Received: "));
      Serial.println(value);
      int current = atoi(value);

      // write the current state to the power switch tail
      digitalWrite(LAMP, current==1 ? HIGH : LOW);
      Serial.println(F("Done"));
    }
  }
}

void publishButton()
{
  // grab the current state of the button
  //Serial.print(F("B?"));
  current = digitalRead(BUTTON);
  if (current != last)
  {
    int32_t value = (current == LOW ? 1 : 0);

    // Now we can publish stuff!
    Serial.print(F("\nSending button value: "));
    Serial.print(value);
    Serial.print("... ");

    if (! button.publish(value))
      Serial.println(F("Failed."));
    else
      Serial.println(F("Success!"));

    // save the button state
    last = current;
  }
}

void publishPhotocell()
{
  //Serial.print(F("A?"));
  // grab the current state of the photocell
  currentA = analogRead(PHOTOCELL);

  // return if the value hasn't changed
  if (abs(currentA - lastA) > 5)
  {
    // Now we can publish stuff!
    Serial.print(F("\nSending photocell value: "));
    Serial.print(currentA);
    Serial.print("... ");

    if (! photocell.publish((int32_t)currentA))
      Serial.println(F("Failed."));
    else
      Serial.println(F("Success!"));

    // save the photocell state
    lastA = currentA;
  }
}
// connect to adafruit io via MQTT
void connect() {

  Serial.print(F("Connecting to Adafruit IO... "));

  int8_t ret;

  while ((ret = mqtt.connect()) != 0) {

    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if (ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(5000);

  }

  Serial.println(F("Adafruit IO Connected!"));

}
