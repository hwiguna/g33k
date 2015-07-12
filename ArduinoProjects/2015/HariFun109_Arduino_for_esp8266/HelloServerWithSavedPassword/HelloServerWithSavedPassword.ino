#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

//-- Credentials --
const int maxStrLength = 50;
char ssid[maxStrLength];
char password[maxStrLength];
int addr = 0;

ESP8266WebServer server(80);
 
const int led = 13;

void Load(char str[])
{
  EEPROM.begin(512);

  for (int i = 0; (addr+i) < 512; i++)
  {
    str[i] = EEPROM.read(addr+i);
    if (str[i]==0) {
      addr += (i+1); // Skip loaded data
      break;
    }
  }
  
  Serial.println();
  Serial.print("str=");
  Serial.println(str);
}
 
void handle_root() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  delay(100);
  digitalWrite(led, 0);
}
 
void ReadCredentials()
{
  addr = 0;
  Load(ssid);
  Load(password);
}

void setup(void)
{
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  
  ReadCredentials();
  Serial.print("**ssid=");
  Serial.println(ssid);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", handle_root);
  
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
} 
