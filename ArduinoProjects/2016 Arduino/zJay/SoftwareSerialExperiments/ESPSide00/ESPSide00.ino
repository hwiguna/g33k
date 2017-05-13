
#include <SoftwareSerial.h>

SoftwareSerial swSer(2, 0, false, 256); // (rx=gpio2, tx=gpio0, invert, buffSize)

void setup() {
  Serial.begin(115200);
  swSer.begin(115200);

  delay(1000);
  Serial.println("\nSoftware serial test started");

  for (char ch = ' '; ch <= 'z'; ch++) {
    swSer.write(ch);
  }
  swSer.println("");

}

void loop() {
  while (swSer.available() > 0) {
    Serial.write(swSer.read());
  }
  while (Serial.available() > 0) {
    swSer.write(Serial.read());
  }

}
