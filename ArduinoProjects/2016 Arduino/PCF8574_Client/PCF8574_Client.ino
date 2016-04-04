/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

// Declare and set these two variables here or in an include file
//const byte credentialCount = 2; //IMPORTANT! Change this to match how many credentials you have!
//const char* credentials[] =
//{
//  "ssid1","pwd1",
//  "ssid2","pwd2"
//};
#include "C:\Users\hwiguna\Documents\Creds\creds.txt"

const byte bufMax = 20;
char ssid[bufMax];
char password[bufMax];

int num = 258;

const char* host = "192.168.254.114";

void ScanWiFi()
{
  bool found = false;
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; (i < n) && !found; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.print((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "* ");
      delay(10);

      char foundssid[bufMax];
      WiFi.SSID(i).toCharArray(foundssid, bufMax);

      for (byte i = 0; i < credentialCount; i++)
      {
        if ( strcmp( foundssid, credentials[i*2]) == 0)
        {
          Serial.print("<-- MATCH");
          strcpy(ssid, credentials[i*2]);
          strcpy(password, credentials[i*2 + 1]);
          found = true;
          exit;
        }
      }
      Serial.println();
    }
  }
  Serial.println("");
}


void setup() {
  Serial.begin(115200);
  delay(10);

  ScanWiFi();
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
  delay(2000);
  ++value;

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
  String url = "/inline?state=";
  url += num++;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}

