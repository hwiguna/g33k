//gpsgsm_postwebPage:
// v1. Jay got GPS and SIM to work together
// v2. Hari added phoneDelay, build the url to send to phone.
// v3. add initial delay to timeToPhome
// v4. Also get and send "Speed"

#include <SoftwareSerial.h>
#include <TinyGPS.h>

//-- GPS is at pins 3,2 at 9600 baud --
SoftwareSerial gpsSerial(3, 2); // RX, TX
TinyGPS gps;
float flat, flon, fspeed;

//== Preferences ==
const long phoneDelay = 60; // in seconds

//-- SIM is at pins 7,8 at 19200 baud
SoftwareSerial SIM900(7, 8);
bool hasSentSMS = false;
long timeToPhone = millis() + phoneDelay;
long loopCount = 0;

void setup()
{
  // Use built-in serial for debugging
  Serial.begin(9600);

  // Set the data rate for the SIM
  SIM900.begin(19200);
  SIM900power(HIGH);

  // Give time to log on to network.
  Serial.println("Waiting 20 seconds for GSM to connect...");
  delay(20000);
  Serial.println("GSM READY!");

  // Set the data rate for the GPS
  Serial.println("Open serial for GPS.");
  gpsSerial.begin(9600);

  Serial.println("We should see LOOP x every 5 seconds!");
}

void loop()
{
  Serial.print(">>> LOOP ");
  Serial.println(++loopCount);

  bool newData = false;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 5000;)
  {
    //Serial.write('#');
    while (gpsSerial.available())
    {
      char c = gpsSerial.read();
      Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData) {
    // Interpret the GPS data
    Serial.println("--1-- RECEIVES NEW GPS DATA!");
    gpsdump(gps);

    if (millis() > timeToPhone) {
      SendToPhone();
      timeToPhone = millis() + (phoneDelay*1000);
    }
  }
}

void SIM900power( int val)
// software equivalent of pressing the GSM shield "power" button
{
  Serial.print("::: SIM900power " );
  Serial.println(val);
  digitalWrite(9, val);
}

void SendToPhone()
{
  Serial.println("SubmitHttpPost - started" );
  SubmitHttpPost();
  Serial.println("SubmitHttpPost - finished" );
  delay(5000);
}

void SubmitHttpPost()
{
  SIM900.println("AT+CSQ"); // Signal quality check

  delay(100);

  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.

  SIM900.println("AT+CGATT?"); //Attach or Detach from GPRS Support
  delay(100);

  ShowSerialData();
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);

  ShowSerialData();

  SIM900.println("AT+SAPBR=3,1,\"APN\",\"phone\"");//setting the APN, Access point name string
  delay(4000);

  ShowSerialData();

  SIM900.println("AT+SAPBR=1,1");//setting the SAPBR
  delay(2000);

  ShowSerialData();

  SIM900.println("AT+HTTPINIT"); //init the HTTP request

  delay(2000);
  ShowSerialData();

  //-- Build the url --
  //hardcoded worked: SIM900.println("AT+HTTPPARA=\"URL\",\"www.codehunter.info/sim900testdata/InsertTemp.php?Lat=40.22981&Lon=-74.77816\"");// setting the httppara, the second parameter is the website you want to access
  String url = "AT+HTTPPARA=\"URL\",\"http://www.codehunter.info/sim900testdata/InsertTemp.php?Lat=";
  url += String(flat, 5);
  url += "&Lon=";
  url += String(flon, 5);
  url += "&Speed=";
  url += String(fspeed, 0);
  url += "\"";

  //-- Send the URL --
  SIM900.println(url);
  delay(1000);

  ShowSerialData();

  SIM900.println("AT+HTTPACTION=0");//submit the request
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!SIM900.available());

  ShowSerialData();

  SIM900.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
  //changeLed();
  ShowSerialData();

  //  SIM900.println("");
  // delay(100);
}

void changeLed()
{

}


void ShowSerialData()
{
  while (SIM900.available() != 0)
    Serial.write(char (SIM900.read()));
}



/*
void sendSMS()
{
  Serial.println("*** Sending SMS... ***");

  // AT command to send SMS message
  SIM900.print("AT+CMGF=1\r"); delay(100);

  // recipient's mobile number, in international format
  SIM900.println("AT + CMGS = \"+16099541532\""); delay(100);

  //-- message to send --
  // http://maps.google.com/?q=40.22981,-74.77947
  SIM900.print("http://maps.google.com/?q="); delay(100);
  printToSMS(flat, 5); SIM900.print(","); printToSMS(flon, 5); delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); delay(100);
  SIM900.println();

  // give module time to send SMS, then turn off SIM module
  delay(5000);
  //SIM900power(LOW);

  Serial.println("SIM900 powered off");
}
*/


void gpsdump(TinyGPS &gps)
{
  long lat, lon;
  unsigned long age, date, time, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned short sentences, failed;

  // gps.get_position(&lat, &lon, &age);
  // Serial.print(lat); Serial.print(","); Serial.print(lon);
  // Serial.println();

  Serial.println("--2-- Getting GPS Position");;
  gps.f_get_position(&flat, &flon, &age);
  fspeed = gps.f_speed_mph();
  
  Serial.println("--3-- Dumping GPS Position");;
  printFloat(flat, 5); Serial.print(","); printFloat(flon, 5); printFloat(fspeed, 0); Serial.println("");

  Serial.println("--4-- Exiting gpsdump");;
}

void printBase(double number, int digits, bool toSMS)
{
  Serial.println("::: printBase");

  // Handle negative numbers
  if (number < 0.0) {
    if (toSMS)
      SIM900.print('-');
    else
      Serial.print('-');
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  if (toSMS)
    SIM900.print(int_part);
  else
    Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    if (toSMS)
      SIM900.print(".");
    else
      Serial.print(".");
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0) {
    remainder *= 10.0;
    int toPrint = int(remainder);
    if (toSMS)
      SIM900.print(toPrint);
    else
      Serial.print(toPrint);

    remainder -= toPrint;
  }

  Serial.println("::: Exiting printBase");
}

void printToSMS(double number, int digits)
{
  Serial.println("::: printToSMS");
  printBase(number, digits, true);
}

void printFloat(double number, int digits)
{
  Serial.println("::: printFloat");
  printBase(number, digits, false);
}

