//AT+RST
//AT+CWMODE=1
//AT+CWJAP="Firefly24","PASSWORD"
//AT+CIPSTART="TCP","184.168.46.67",80

// AT+CIPSEND=70
// 43+2+19+4

// 0        1         2         3         4         5         6         7         8
// 12345678901234567890123456789012345678901234567890123456789012345678901234567890
// GET /data/2.5/weather?q=Lincoln,Ne HTTP/1.0
// 0        1         2         3         4         5         6         7         8
// 12345678901234567890123456789012345678901234567890123456789012345678901234567890
// Host: 162.243.44.32
  
  
#include <SoftwareSerial.h>
#include "password.h"
#define SSID "-------"        //your wifi ssid here
 
//#define DST_IP "162.243.44.32" // "api.openweathermap.org"
//#define HOST "api.openweathermap.org"
#define DST_IP "220.181.111.85" // "baidu.com"
#define HOST "baidu.com"


//#define WIFI_BAUD  115200
#define WIFI_BAUD  57600
#define PC_BAUD    19200

SoftwareSerial dbgSerial(10, 11); // RX, TX
 
char myChar;
String line;
 
void setup()
{
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
 
  //blink led13 to indicate power up
  for(int i = 0; i<15; i++)
  {
   digitalWrite(13,HIGH);
   delay(50);
   digitalWrite(13,LOW);
   delay(50);
  }
 
  // Open serial communications for WiFi module:
  Serial.begin(WIFI_BAUD); // firmware v0.922 defaults to 9600. use AT+CIOBAUD=115200 to change speed.
  // Set time to wait for response strings to be found
  Serial.setTimeout(5000);
 
  //Open software serial for debugging - must use serial to usb (FTDI) adapter
  //dbgSerial.begin(19200); //can't be faster than 19200 for softserial
  dbgSerial.begin(PC_BAUD);   //38400 softserial works fine for me
      
  dbgSerial.println("ESP8266 Demo");
  delay(100);
  
  //-- RESET --
  Println("AT");
  //delay(1000);
  WaitFor("OK");
  dbgSerial.println("Module is ready");
  
  //-- CONNECT TO WIFI --
  delay(1000);
  boolean connected=false;
  for(int i=0;i<5;i++)
  {
    if(connectWiFi())
    {
      connected = true;
      break;
    }
  }
  if (!connected)
  {
    //die
    while(1);
  }
 
  delay(5000);
  HttpGetTest();
}
 
void loop()
{

}
 
void WebServerTest()
{
  //-- WEBSERVER MODE
  Println("AT+CIPMUX=1");
  WaitFor("OK");
  
  //-- CONNECT TO A WEBSITE --
  String cmd = "AT+CIPSERVER=1,80";
  Println(cmd);
  WaitFor("OK");

  //-- ASK FOR A WEB PAGE --
  cmd = "GET /data/2.5/weather?q=Lincoln,Ne HTTP/1.1\r\nHost: ";
  cmd += HOST;
  cmd += "\r\n";
 
  String len = String( cmd.length() );
  Println("AT+CIPSEND=" + len);
  WaitFor("> ");
  
  Print(cmd);
 
  delay(2000);
  //Serial.find("+IPD");
  while (true) //Serial.available())
  {
   int c = Serial.read();
   if (c!=-1) {
     dbgSerial.write(c);
     if(c=='\r') dbgSerial.print('\n');
   }
   delay(50);
  }
 
 dbgSerial.println();
 dbgSerial.println("====");
 delay(5000);
}

void HttpGetTest()
{

  //-- SINGLE CONNECTION MODE --
  Println("AT+CIPMUX=0");
  WaitFor("OK");
  
  //-- CONNECT TO A WEBSITE --
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += DST_IP;
  cmd += "\",80";
  Println(cmd);
  WaitFor("OK");

  //-- ASK FOR A WEB PAGE --
  cmd = "GET / HTTP/1.0\r\n\r\n";
 
  String len = String( cmd.length() );
  Println("AT+CIPSEND=" + len);
  WaitFor("> ");
  
  Print(cmd);
 
  delay(2000);
  //Serial.find("+IPD");
  while (true) //Serial.available())
  {
   int c = Serial.read();
   if (c!=-1) {
     dbgSerial.write(c);
     if(c=='\r') dbgSerial.print('\n');
   }
   delay(50);
  }
 
 dbgSerial.println();
 dbgSerial.println("====");
 delay(5000);
}

boolean connectWiFi()
{
  //-- MODE 1 = CLIENT MODE --
  Println("AT+CWMODE=1");
  WaitFor("no chng");
  
  //-- CONNECT TO ACCESS POINT --
  String cmd="AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  Println(cmd);
  WaitFor("OK");

  dbgSerial.println("OK, Connected to WiFi.");
  return true;
}

void Print(String str)
{
  dbgSerial.print("PRINT='");
  dbgSerial.print(str);
  dbgSerial.println("'");

  Serial.print(str);
}

void Println(String str)
{
  dbgSerial.print("PRINTLINE='");
  dbgSerial.print(str);
  dbgSerial.println("'");

  Serial.println(str);
}

String ReadLine()
{
  String line = "";
  
  line = Serial.readStringUntil(13);
  Serial.readStringUntil(10);
  
  dbgSerial.print("LINE='");
  dbgSerial.print(line);
  dbgSerial.println("'");
  
  return line;
}

void WaitFor(String whatToWaitFor)
{
  String line;
  while (line != whatToWaitFor)
    line = ReadLine();
}
