// ESP8266 LED Matrix Server
// Responds to /dly/x where low x means faster scroll speed.
// Hari Wiguna, 2015

//--- WIFI ---

#include <ESP8266WiFi.h>

const char* ssid = "Firefly24";
const char* password = "........";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);


//--- MATRIX ---

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int offset = 0;
String msg = " Hello YouTube! ";
int msgLength = msg.length();
String outStr = "";
int val = 0;
int dly = 100;
unsigned long nextRefresh = millis();

void SetupMatrix()
{
  pinMode(A0, INPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  Wire.pins(0, 2); // <-- IMPORTANT!!! call this BEFORE initializing AdaFruit matrix (which calls wire.begin() with no parameters!
  matrix.begin(0x70);  // pass in the address
}

void MatrixLoop()
{
  if (millis() > nextRefresh)
  {
    // Draw the message with increasing negative offset to "scroll" it
    for (int i = 0; i < msgLength; i++)
      matrix.drawChar(i * 6 - offset, 0, msg[i], 1, 0, 1);

    matrix.writeDisplay();  // Actually update the display

    if (offset++ >= msgLength * 6) offset = 0;
    nextRefresh = millis() + dly;
  }
}
void setup() {

  Serial.begin(9600);
  delay(10);

  // Connect to WiFi network
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

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  SetupMatrix();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    MatrixLoop();
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  if (req.indexOf("/gpio/0") != -1)
  {
    val = 0;
    dly = dly * 40 / 100;
    if (dly <= 30) dly = 200;
    outStr = "GPIO is now 0";
  }
  else if (req.indexOf("/gpio/1") != -1) {
    val = 1;
    outStr = "GPIO is now 1";
  }
 else if (req.indexOf("/dly/") != -1)
 {
    int paramBegin = req.indexOf("/dly/")+5;
    int paramEnd = req.indexOf(" ", paramBegin);
    String param = req.substring(paramBegin, paramEnd);
    dly = param.toInt();
    Serial.print("dly=");
    Serial.println(dly);
    outStr = "dly is now " + String(dly);
 }
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  s += outStr;
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}

