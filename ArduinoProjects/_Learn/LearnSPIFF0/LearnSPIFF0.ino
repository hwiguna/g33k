#include "FS.h"

void setup() {
Serial.begin(115200);
Serial.print("SPIFFS begin=");
Serial.println(SPIFFS.begin());

Serial.print("file open: ");
File f = SPIFFS.open("/test.htm", "r");
Serial.println(f ? "OK" : "err");

char buffer[100];
int length = 100;
int nRead = f.readBytes(buffer, length);

Serial.print("nRead= ");
Serial.println(nRead);

buffer[nRead]=0; // Terminate the string
Serial.print("*");
Serial.print(buffer);
Serial.println("*");

}

void loop() {
  // put your main code here, to run repeatedly:

}
