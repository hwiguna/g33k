#include <MsTimer2.h>

//-- Ports --
int led0 = 11;
int led1 = 13;

//-- Layer counter --
uint8_t z = 0;

//-- Screen buffer --
uint8_t arr[2];

void Refresh()
{
  //-- Turn off previous layer --
  if (z==0) digitalWrite(led0, LOW);
  if (z==1) digitalWrite(led1, LOW);

  //-- Compute new layer --
  z++; if (z>=8) z=0;

  //-- Turn on new layer (will stay on till next time timer fires) --
  if (z==0) digitalWrite(led0, arr[0]);
  if (z==1) digitalWrite(led1, arr[1]);
}

void setup()
{
  arr[0]=255;
  pinMode(led0, OUTPUT);     
  pinMode(led1, OUTPUT);     
  MsTimer2::set(2,Refresh);
  MsTimer2::start();
}

void loop()
{
  
  arr[0] = 255-arr[0];
  arr[1] = 255-arr[1];
  delay(10);
}
