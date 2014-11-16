#define SSID "[WiFi Access Point Name]"
#define PASS "[WiFi Password]"
#define KEY "[ThingSpeak Key]"

#include "Credentials.h"
#include<stdlib.h>
#include <SoftwareSerial.h>

#define IP "184.106.153.149" // thingspeak.com
#define buttonPin 4

SoftwareSerial monitor(10, 11); // RX, TX

void setup()
{
  monitor.begin(9600);
  monitor.println("*** Thingspeaker ***");
  
  Serial.begin(9600);
  Serial.setTimeout(5000);
  pinMode(buttonPin,INPUT_PULLUP);
  
  //-- Talk to ESP8266 --
  delay(1000);
  sendDebug("AT");
  //delay(5000);
  if(Serial.find("OK")){
    monitor.println("RECEIVED: OK");
    connectWiFi();
  }
}

void loop(){
  for (int i=10; i>=0; i--)
  {
    int field1Val = analogRead(A0);
    int field2Val = 1 -  digitalRead(buttonPin);

    //-- Print every second --
    monitor.print(i);
    monitor.print(": field1Val="); monitor.print(field1Val);
    monitor.print(" field2Val="); monitor.println(field2Val);
    
    //-- Send every 15 seconds --
    if (i==0) SendToThingSpeak(field1Val, field2Val);
    delay(1000);
  }
}

void SendToThingSpeak(int field1Val, int field2Val){
  //-- Connect to ThingSpeak --
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  sendDebug(cmd);
  //delay(2000);
  if(Serial.find("Error")){
    monitor.print("RECEIVED: Error");
    return;
  }
  
  //-- The page request string (including the data as part of the URL) --
  cmd = "GET /update.html";
  cmd += "?key=";
  cmd += KEY;
  cmd += "&field1=";
  cmd += field1Val;
  cmd += "&field2=";
  cmd += field2Val;
  cmd += "\r\n";
  monitor.print("command: ");
  monitor.print(cmd);
  
  //-- Tell ThingSpeak how long is the page request --
  String request = "AT+CIPSEND=" + String(cmd.length());
  sendDebug(request);
//  Serial.print("AT+CIPSEND=");
//  Serial.println(cmd.length());
  if(Serial.find(">")){

    //-- Send the page request --
    //monitor.print("SEND> ");
    //monitor.print(cmd);
    //Serial.print(cmd);
    sendDebug(cmd);
    if(Serial.find("OK")){
      monitor.println("RECEIVED: OK");
    }else{
      monitor.println("RECEIVED: Error");
    }
    
  }else{
    sendDebug("AT+CIPCLOSE");
  }
  
}

void sendDebug(String cmd){
  monitor.print("SEND: ");
  monitor.println(cmd);
  Serial.println(cmd);
} 
 
boolean connectWiFi(){
  //-- Set to Client Mode. 1=Client, 2=Access Point, 3=Client & AP --
  sendDebug("AT+CWMODE=1");
  delay(2000);
  
  //-- Connect to WiFi access point --
  String cmd="AT+CWJAP=\""; // AT+CWJAP=quote
  cmd += SSID;
  cmd += "\",\""; // quote, comma, quote
  cmd += PASS;
  cmd += "\"";    // quote
  sendDebug(cmd);
  //delay(5000);
  if(Serial.find("OK")){
    monitor.println("RECEIVED: OK");
    return true;
  }else{
    monitor.println("RECEIVED: Error");
    return false;
  }
}
