// Analog Input Web Client
// sends ADC (Analog Digital Converter) value
// as a web request to ESP8266 LED Matrix Server
// Hari Wiguna, 2015

#include <ESP8266WiFi.h>

const char* ssid     = "Firefly24";
const char* password = "........";

const char* host = "192.168.254.112";

const int switchPin = 0;
int value = 0;
int previousValue = 1;

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(switchPin, INPUT);
  pinMode(A0, INPUT);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  // Read and map the ADC input so the output is 10 through 100
  value = map(analogRead(A0), 0,1023, 10,100);

  // Only send value to Server if it changes "significantly"
  if ( abs(value-previousValue) > 5 )
  {
    previousValue = value;

    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }

    // We now create a URI for the request
    String url = "/dly/";
    url += String(value);

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    delay(10);

    // Read all the lines of the reply from server and print them to Serial
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");
  }
  delay(10);
}

