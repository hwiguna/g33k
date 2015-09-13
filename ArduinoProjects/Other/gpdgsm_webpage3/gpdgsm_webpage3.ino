// v3 - swap order of include, use "L" suffix to indicate long constants
// v4 - assign lat and lon to float first, before dividing it.

#include <TinyGPS.h>
#include <SoftwareSerial.h>

//=== GPS ===
SoftwareSerial GPS(3, 2); // rx = pin 0 tx = pin 1
unsigned long fix_age;
TinyGPS gps;
void gpsdump(TinyGPS &gps);
bool feedgps();
void getGPS();
long lat, lon;
float latitude, longitude;

//== PHONE ==
SoftwareSerial SIM900(7, 8); // configure software serial port

//== OTHER VARIABLES ==
bool hasSubmitHttp = false;

void setup() {
  //-- Initiliaze Serial Monitor for debugging --
  Serial.begin(9600);
  
  //-- Initialize GPS --
  GPS.begin(9600);

  //-- Initialize Phone --
  SIM900.begin(19200);
  SIM900power();
  Serial.print("power up" );
  delay(20000);
}

void loop()
{
  getLatLong();
  if (!hasSubmitHttp)
  {
    hasSubmitHttp = true;
    SubmitHttpPost();
  }
}

//=== GPS ===

void getLatLong()
{
  long lat, lon;
  unsigned long fix_age, time, date, speed, course;
  unsigned long chars;
  unsigned short sentences, failed_checksum;

  // retrieves +/- lat/long in 100000ths of a degree
  gps.get_position(&lat, &lon, &fix_age);

  getGPS();

  latitude = lat;
  longitude = lon;
  latitude = latitude / 100000;
  longitude = longitude / 100000;

  Serial.print(latitude, 5); //GPS LAT
  Serial.print(",");  //comma between the LAT and LON is needed for google maps
  Serial.println(longitude, 5); //GPS Lon
}

void getGPS() {
  bool newdata = false;
  unsigned long start = millis();
  // Every 1 seconds we print an update
  while (millis() - start < 1000)
  {
    if (feedgps ()) {
      newdata = true;
    }
  }
  if (newdata)
  {
    gpsdump(gps);
  }
}

bool feedgps() {
  while (GPS.available())
  {
    if (gps.encode(GPS.read()))
      return true;
  }
  return 0;
}

void gpsdump(TinyGPS &gps)
{
  //byte month, day, hour, minute, second, hundredths;
  gps.get_position(&lat, &lon);
  latitude = lat;
  longitude = lon;
  {
    feedgps(); // If we don't feed the gps during this long routine, we may drop characters and get checksum errors
  }
}

//=== PHONE ===

void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
}

void ShowSerialData()
{
  while (SIM900.available() != 0)
    Serial.write(char (SIM900.read()));
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
  //Original: SIM900.println("AT+HTTPPARA=\"URL\",\"http://www.codehunter.info/sim900testdata/InsertTemp.php?Temp=12334567890\"");// setting the httppara, the second parameter is the website you want to access
  // http://www.codehunter.info/sim900testdata/InsertTemp.php?Lat=40.22981&Lon=-74.77813
  String url = "AT+HTTPPARA=\"URL\",\"http://www.codehunter.info/sim900testdata/InsertTemp.php?Lat=";
  url += String(latitude, 5);
  url += "&Lon=";
  url += String(longitude, 5);
  url += "\"";

  //-- Send the URL --
  SIM900.println(url);
  delay(1000);
  ShowSerialData();

  SIM900.println("AT+HTTPACTION=0");//submit the request
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while (!SIM900.available());
  ShowSerialData();

  SIM900.println("AT+HTTPREAD");// read the data from the website you access
  delay(2000);
  ShowSerialData();

//  SIM900.println("");
//  delay(100);
}
