// Version 1. Gets GPS data, and sends via SMS once.
// Version 2. Fixed bug where start was repeatedly re-set in loop()
// version 3. Re enable GSM.  Added more debugging messages

#include <SoftwareSerial.h>
#include <TinyGPS.h>

//-- GPS is at pins 3,2 at 9600 baud --
SoftwareSerial gpsSerial(3, 2); // RX, TX
TinyGPS gps;
float flat, flon;
//void gpsdump(TinyGPS &gps);
//void printFloat(double f, int digits = 2);

//-- SIM is at pins 7,8 at 19200 baud
SoftwareSerial SIM900(7, 8);
bool hasSentSMS = false;

void setup()
{
  // Use built-in serial for debugging
  Serial.begin(9600);

  // Set the data rate for the GPS
  gpsSerial.begin(9600);

  // Set the data rate for the SIM
  SIM900.begin(19200);
  SIM900power(HIGH);
  
  // Give time to log on to network.
  Serial.println("Waiting 20 seconds for GSM to connect...");
  delay(20000);  
  Serial.println("READY!");
}

void loop()
{
  bool newData = false;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 5000;)
  {
    //Serial.write('#');
    while (gpsSerial.available())
    {
      char c = gpsSerial.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData) {
    // Interpret the GPS data
    gpsdump(gps);

    // SendSMS if we have not sent one yet.
    if (!hasSentSMS) {
      sendSMS();
      hasSentSMS = true;
    }
  }
}

void SIM900power( int val)
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, val);
}

void sendSMS()
{
  Serial.println("*** Sending SMS... ***");
  
  // AT command to send SMS message
  SIM900.print("AT+CMGF=1\r"); delay(100);
  
  // recipient's mobile number, in international format
  SIM900.println("AT + CMGS = \"+16099541532\""); delay(100);
  
  //-- message to send --
  // Lat, Long
  printToSMS(flat, 5); SIM900.print(","); printToSMS(flon, 5); delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); delay(100);
  SIM900.println(); 
  
  // give module time to send SMS, then turn off SIM module
  delay(5000);                                     
  SIM900power(LOW);

  Serial.println("SIM900 powered off");
}

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

  gps.f_get_position(&flat, &flon, &age);
  printFloat(flat, 5); Serial.print(","); printFloat(flon, 5); Serial.println("");
}

void printFloat(double number, int digits, bool toSMS)
{
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
}

void printToSMS(double number, int digits)
{
  printFloat(number, digits, true);
}

void printFloat(double number, int digits)
{
  printFloat(number, digits, false);
}
