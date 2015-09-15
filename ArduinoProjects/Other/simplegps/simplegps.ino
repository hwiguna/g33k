

#include <TinyGPS.h>
#include <SoftwareSerial.h>

unsigned long fix_age;

SoftwareSerial GPS(3,2); // rx = pin 0 tx = pin 1 
TinyGPS gps;
void gpsdump(TinyGPS &gps);
bool feedgps();
void getGPS();
long lat, lon;
float LAT, LON;

void setup(){
  GPS.begin(9600);
  Serial.begin(9600);
}

void loop(){
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

