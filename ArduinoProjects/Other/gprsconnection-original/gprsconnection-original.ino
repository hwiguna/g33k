#include <TinyGPS.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // configure software serial port

unsigned long fix_age;

SoftwareSerial GPS(3,2); // rx = pin 0 tx = pin 1 
TinyGPS gps;
void gpsdump(TinyGPS &gps);
bool feedgps();
void getGPS();
long lat, lon;
float LAT, LON;

void setup() {     
 GPS.begin(9600);
delay(5000);
 SIM900.begin(19200);
  Serial.begin(19200); 
    SIM900power();
  Serial.print("power up" );
  delay(20000); 

}

void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
//  digitalWrite(9, LOW);
 // delay(5000);
}
 
void loop()
{
      long lat, lon;
  unsigned long fix_age, time, date, speed, course;
  unsigned long chars;
  unsigned short sentences, failed_checksum;

  // retrieves +/- lat/long in 100000ths of a degree
  gps.get_position(&lat, &lon, &fix_age);

  getGPS();

  Serial.print(LAT/100000,5);  //GPS LAT
  Serial.print(",");  //comma between the LAT and LON is needed for google maps
Serial.println(LON/100000,5);  //GPS Lon


  Serial.println("SubmitHttpPost - started" );
  SubmitHttpPost();
  Serial.println("SubmitHttpPost - finished" );
  delay(5000);
  

}

void getGPS(){
  bool newdata = false;
  unsigned long start = millis();
  // Every 1 seconds we print an update
  while (millis() - start < 1000)
  {
    if (feedgps ()){
      newdata = true;
    }
  }
  if (newdata)
  {
    gpsdump(gps);
  }
}

bool feedgps(){
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
  LAT = lat;
  LON = lon;
  {
    feedgps(); // If we don't feed the gps during this long routine, we may drop characters and get checksum errors
  }
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
 
  SIM900.println("AT+HTTPPARA=\"URL\",\"www.codehunter.info/sim900testdata/InsertTemp.php?Lat=40.22981&Lon=-74.77816\"");// setting the httppara, the second parameter is the website you want to access
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
  while(SIM900.available()!=0)
    Serial.write(char (SIM900.read()));
}
