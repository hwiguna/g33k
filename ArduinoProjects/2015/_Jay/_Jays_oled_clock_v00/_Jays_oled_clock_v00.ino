/*
  Simple RTC for Arduino Zero

 Demonstrates the use of the RTC library for the Arduino Zero

 This example code is in the public domain

 http://arduino.cc/en/Tutorial/SimpleRTC

*/

#include <RTCZero.h>

/* Create an rtc object */
RTCZero rtc;

/* Change these values to set the current initial time */
const uint8_t seconds = 0;
const uint8_t minutes = 0;
const uint8_t hours = 16;

/* Change these values to set the current initial date */
const uint8_t day = 15;
const uint8_t month = 6;
const uint8_t year = 15;

void setup()
{
  Serial.begin(9600);

  rtc.begin(H24); // initialize RTC 24H format. The dual option is H12

  // Set the time
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);

  // Set the date
  rtc.setDay(day);
  rtc.setMonth(month);
  rtc.setYear(year);

  // you can use also
  //rtc.setTime(hours, minutes, seconds);
  //rtc.setDate(day, month, year);

  // you can use also to set it with the compile time
  rtc.setTime(__TIME__);
  rtc.setDate(__DATE__);
}

String Pad(uint8_t num)
{
  String out = "00" + String(num);
  byte len = out.length();
  return out.substring( len-2, len);
}

byte prevSeconds;

void loop()
{
  byte newSeconds = rtc.getSeconds();
  if (newSeconds != prevSeconds)
  {
    prevSeconds = newSeconds;
    String dateStr = Pad(rtc.getDay()) + "/" + Pad(rtc.getMonth()) + "/" + Pad(rtc.getYear());
    Serial.print(dateStr);
    
    Serial.print("\t");
    
    String timeStr = Pad(rtc.getHours()) + ":" + Pad(rtc.getMinutes()) + ":" + Pad(rtc.getSeconds());
    Serial.println(timeStr);
  }

  delay(100);
}
