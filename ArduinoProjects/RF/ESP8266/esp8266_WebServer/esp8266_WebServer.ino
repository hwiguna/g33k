#define SSID "[WiFi Access Point Name]"
#define PASS "[WiFi Password]"
#define KEY "[ThingSpeak Key]"

#include "Credentials.h"
#include<stdlib.h>
#include <SoftwareSerial.h>

#define IP "184.106.153.149" // thingspeak.com
#define buttonPin 4

SoftwareSerial monitor(10, 11); // RX, TX

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
//unsigned long ignoreTill = 0;
boolean IsResponding = false;

//-- WebServer globals --
String requestId;


void setup()
{
  monitor.begin(9600);
  monitor.println("*** Webserver ***");
  
  Serial.begin(9600);
  Serial.setTimeout(5000);
  pinMode(buttonPin,INPUT_PULLUP);
  
  //-- Talk to ESP8266 --
  delay(1000);
  //Send("AT");
  //delay(5000);
  //if(Serial.find("OK")){
  //  monitor.println("RECEIVED: OK");
  Send("AT","OK");
    if (connectWiFi())
    {
      if (StartWebserver())
      {
        monitor.println("WebServer Ready");
      }
    }
  //}
}

void loop(){
  if (stringComplete) {
    boolean hasIPD = inputString.indexOf("+IPD") != -1;
    boolean hasHttp = inputString.indexOf("HTTP") != -1;
    if (hasIPD && !hasHttp) {
      // We only got part of the request notification, keep appending request to inputString
      // monitor.println("Partial!");
    }
    else
    {
//      String request = String(inputString); // Make a copy so we won't be bothered if serialEvent fires while we're processing.
//      if (request.startsWith("192.")) {
//         monitor.println(request); 
//      }
//      inputString = "";

      if (ProcessRequest(inputString)) {
        //ignoreTill = millis() + 5000;
        Respond("HELLO");
      }
      inputString = "";
    }
    stringComplete = false;
  }
}

void serialEvent()
{
  if (!IsResponding)
  {
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read(); 
      // add it to the inputString:
      inputString += inChar;
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '\n') 
      {
        //if (millis() > ignoreTill) {
          stringComplete = true;
        //}
      }
    }
  }
}

void Send(String cmd){
  monitor.print("SEND: ");
  monitor.println(cmd);
  Serial.println(cmd);
} 

void Send(String cmd, char* waitFor){
  IsResponding = false;
  monitor.print("SEND... ");
  monitor.println(cmd);
  Serial.println(cmd);
  
  if (Serial.find(waitFor)){
    monitor.print("RECEIVED: ");
    monitor.println(waitFor);
  }
  IsResponding = true;
} 

 
boolean connectWiFi(){
  //-- Set to Client Mode. 1=Client, 2=Access Point, 3=Client & AP --
  Send("AT+CWMODE=1");
  delay(2000);
  
  //-- Connect to WiFi access point --
  String cmd="AT+CWJAP=\""; // AT+CWJAP=quote
  cmd += SSID;
  cmd += "\",\""; // quote, comma, quote
  cmd += PASS;
  cmd += "\"";    // quote
  Send(cmd);
  //delay(5000);
  if(Serial.find("OK")){
    monitor.println("RECEIVED: OK");
    return true;
  }else{
    monitor.println("RECEIVED: Error");
    return false;
  }
}

boolean StartWebserver()
{
  boolean success = false;
  
  Send("AT+CWMODE=1", "OK");    // 1=Client, 2=Access Point, 3=Client & AP
  Send("AT+CIPMUX=1");    // 0 = Single Connection, 1 = Multiple Connection
  //Send("AT+CIFSR", "OK");      // Display Webserver IP Address
  Send("AT+CIPSTO=30", "OK");  // Set Timeout
  if(Serial.find("OK")){
    Send("AT+CIPSERVER=1,80");   // 0=close, 1=open, followed by port#.
    success = true;
  }
  
  return success;
}

boolean ProcessRequest(String request)
{
  boolean success = false;
  
  if (request.indexOf("/CMD/")!=-1)
  {
    int ipdPos = request.indexOf("+IPD");  // +IPD
    int firstcommaPos = request.indexOf(",", ipdPos+1); // Comma before requestID
    int secondCommaPos = request.indexOf(",", firstcommaPos+1); // Comma after requestID
    
    requestId = request.substring(firstcommaPos+1,secondCommaPos);
    monitor.print("ID=");
    monitor.println(requestId);
    
    //-- /A/Port/Value --
    int slashPos1 = request.indexOf("/", secondCommaPos+1);  // CMD (PageName)
    int slashPos2 = request.indexOf("/", slashPos1+1); // A)nalog or D)igital
    int slashPos3 = request.indexOf("/", slashPos2+1); // Arduino Port
    int slashPos4 = request.indexOf("/", slashPos3+1); // Value
    int spacePos = request.indexOf(" ", slashPos4+1); // end of value string

    //-- Arduino Port Type --
    String portType = request.substring(slashPos2+1, slashPos3);
    monitor.print("Type=");  monitor.println(portType);
    
    if (portType=="D" || portType=="A")
    {
      //-- Arduino Port --
      String cmd = request.substring(slashPos3+1, slashPos4);
      monitor.print("CMD=");  monitor.println(cmd);
      
      //-- Value --
      String val = request.substring(slashPos4+1, spacePos);
      monitor.print("Value=");  monitor.println(val);
      
      digitalWrite(13, val.toInt());
    }
    else
    {
      monitor.println("Request is not D or A. Ignored.");
    }
    
    success = true;
  }
  else
  {
    if (request.indexOf("192.168.")!=-1)
    {
      monitor.print("SERVER: ");  monitor.println(request);
    }
  }
  
  return success;
}

boolean Respond(String payload)
{
  String content = payload; // + "\r\n";
  int contentLength = content.length();
  String header = "HTTP/1.1 200 OK\r\n";
  header += "Date: Thu, 1 Jan 2000 12:00:00 GMT\r\n";
  header += "Server: ESP8266/0.0.0\r\n";
  header += "Last-Modified: Thu, 1 Jan 2000 12:00:00 GMT\r\n";
  header += "ETag: \"000-0000000-00000000\"\r\n";
  header += "Content-Type: text/html\r\n";
  header += "Content-Length:";
  header += contentLength;
  header += "\r\n";
  header += "Accept-Ranges: bytes\r\n";
  header += "Connection: close\r\n";
  
  int packetLength = header.length() + contentLength + 2;
  
  String sendPacketCmd = "AT+CIPSEND=";
  sendPacketCmd += requestId;
  sendPacketCmd += ",";
  sendPacketCmd += packetLength;
  
  IsResponding = true;
  Send(sendPacketCmd);
  delay(1000);
  
  Send(header);
  //delay(2000);

  Send(content);
  //Send("");
  delay(2000);
  IsResponding = false;
}
