/*
    This sketch sends data via HTTP GET requests to data.sparkfun.com service.

    You need to get streamId and privateKey at data.sparkfun.com and paste them
    below. Or just customize this script to talk to other HTTP servers.

*/

String url = "/devices/HubMon1138AM/messages/events?api-version=2016-02-03";

// What we need to send:
String content = 
"{"
"    ""Command"": ""HubDataUpload"","
"    ""DeviceId"": ""HubMon1138AM"","
"    ""DataDateTime"": ""2/22/2016 4:51:54 PM"","
"    ""SensorsData"": ["
"        {"
"            ""SensorUniqueId"": ""RPI01"","
"            ""SensorValues"": ["
"                {"
"                    ""ReadingDateTime"": ""2/22/2016 4:51:54 PM"","
"                    ""Key"": ""Raw"","
"                    ""Value"": ""666"""
"                }"
"            ]"
"        }"
"    ]"
"}";

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid     = "ng-guest";
const char* password = "dontpanic";

const char* host = "dpliothub.azure-devices.net";
const char* streamId   = "o8yZxwAv5JI1Xq7NXDwa"; // aka PublicKey
const char* privateKey = "yz7YDrMkoWUA6yx86kEM";

int lastAnalog = -100;

void setup() {
  Serial.begin(115200);
  delay(10);

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

int value = 0;

void loop() {

  int analog = analogRead(A0);
  if ( abs(analog - lastAnalog) > 10)
  {
    lastAnalog = analog;

    Serial.print("POSTing to: ");
    Serial.println(url);

    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }

    // This will send the request to the server
    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +

                 //"IoTHub-MessageId: MessageId system property\r\n" +
                 //"IoTHub-CorrelationId: CorrelationId system property\r\n" +
                 "IoTHub-UserId: iothubowner\r\n" +
                 //IoTHub-app-{property name}: {property value}

                 "Content-Type: application/x-www-form-urlencoded\r\n" +
                 "Content-Length: " + content.length() +
                 content + "\r\n" +
                 "Connection: close\r\n\r\n");
    delay(10);

    // Read all the lines of the reply from server and print them to Serial
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");

    delay(500);
  }
}

