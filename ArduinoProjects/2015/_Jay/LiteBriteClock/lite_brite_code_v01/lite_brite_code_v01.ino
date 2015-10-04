// LiteBrite clock for Jay
// Original code uses time.h, updated code uses DS3231
// Hari Wiguna 2015

//#include <Time.h>
#include <Wire.h>
#include <DS3231.h>

//-- RTC --
DS3231 clock;
RTCDateTime dt;

//-- LiteBrite --
int column[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int row[] = {14, 15, 16, 17, 18};

void setup()
{
  //-- RTC --
  clock.begin();
  // Set sketch compiling time
  clock.setDateTime(__DATE__, __TIME__);
  //setTime(9,27,0,27,7,2012);

  //-- LiteBrite --
  for (int i = 0; i < 12; i++) {
    pinMode(column[i], OUTPUT);
    digitalWrite(column[i], LOW);
  }

  for (int j = 0; j < 5; j++) {
    pinMode(row[j], OUTPUT);
    digitalWrite(row[j], HIGH);
  }
}

void loop () {
  //-- RTC --
  dt = clock.getDateTime();

  digitalWrite(column[10], HIGH);
  digitalWrite(column[11], HIGH);
  digitalWrite(column[10], LOW);
  digitalWrite(column[11], LOW);

  switch (dt.hour > 12 ? dt.hour - 12 : dt.hour) {
    case 1:
      one(0);
      break;
    case 2:
      two(0);
      break;
    case 3:
      three(0);
      break;
    case 4:
      four(0);
      break;
    case 5:
      five(0);
      break;
    case 6:
      six(0);
      break;
    case 7:
      seven(0);
      break;
    case 8:
      eight(0);
      break;
    case 9:
      nine(0);
      break;
    case 10:
      one(-3);
      zero(0);
      break;
    case 11:
      one(-3);
      one(0);
      break;
    case 12:
      one(-3);
      two(0);
      break;

  }

  switch (dt.minute / 10) {
    case 0:
      zero(3);
      break;
    case 1:
      one(3);
      break;
    case 2:
      two(3);
      break;
    case 3:
      three(3);
      break;
    case 4:
      four(3);
      break;
    case 5:
      five(3);
      break;
  }

  switch (dt.minute % 10) {
    case 0:
      zero(6);
      break;
    case 1:
      one(6);
      break;
    case 2:
      two(6);
      break;
    case 3:
      three(6);
      break;
    case 4:
      four(6);
      break;
    case 5:
      five(6);
      break;
    case 6:
      six(6);
      break;
    case 7:
      seven(6);
      break;
    case 8:
      eight(6);
      break;
    case 9:
      nine(6);
      break;
      // if nothing else matches, do the default
      // default is optional
  }
}

void allOn() {
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 13; y++) {
      digitalWrite(row[x], LOW);
      digitalWrite(column[y], HIGH);
    }
  }
}

void allOff() {
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 13; y++) {
      digitalWrite(row[x], HIGH);
      digitalWrite(column[y], LOW);
    }
  }
}

void zero(int x) {
  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[1], HIGH);

}

void one(int x) {
  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[4], HIGH);
}

void two(int x) {
  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[0], HIGH);

}

void three(int x) {
  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[0], HIGH);

}

void four(int x) {
  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[4], HIGH);
}

void five(int x) {
  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[0], HIGH);

}

void six(int x) {
  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[1], HIGH);

}

void seven(int x) {
  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[4], HIGH);
}

void eight(int x) {
  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[2], HIGH);

}

void nine(int x) {
  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[0], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[0], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[1], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[1], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[1 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[1 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[2], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[2], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[3], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[3], HIGH);

  digitalWrite(column[2 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[2 + x], LOW);
  digitalWrite(row[4], HIGH);

  digitalWrite(column[3 + x], HIGH);
  digitalWrite(row[4], LOW);
  digitalWrite(column[3 + x], LOW);
  digitalWrite(row[4], HIGH);
}


