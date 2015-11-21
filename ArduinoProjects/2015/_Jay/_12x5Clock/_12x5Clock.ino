#include <Time.h>

int column[]={
  0,1,2,3,4,5,6,7,8,9,10,11};
int row[] = {
  14,15,16,17,18};

int hourButtonPin = 12;   // Other button leg should go to ground, no pullup resistor needed.
int minuteButtonPin = 13; // Other button leg should go to ground, no pullup resistor needed.
unsigned long timeToCheckButtons = 0;

void setup()
{
  setTime(9,27,0,27,7,2012);

  for (int i=0;i<13;i++){
    pinMode(column[i],OUTPUT);
    digitalWrite(column[i],LOW);
  } 

  for (int j=0;j<5;j++){
    pinMode(row[j],OUTPUT);
    digitalWrite(row[j],HIGH);
  }

  //-- Setup button pins --
  pinMode(hourButtonPin,INPUT_PULLUP);
  pinMode(minuteButtonPin,INPUT_PULLUP);
}

void CheckButtons()
{
  if (millis() >= timeToCheckButtons) {
    if (digitalRead(hourButtonPin)==0) {
      int hh = hourFormat12() + 1;
      if (hh>12) hh=1;
      setTime(hh, minute(), 0, 1, 1, 2000);
    }

    if (digitalRead(minuteButtonPin)==0) {
      int mm = minute() + 1;
      if (mm>59) mm=0;
      setTime(hourFormat12(), mm, 0, 1, 1, 2000);
    }
    
    timeToCheckButtons = millis() + 1000;
  }
}

void loop () {

  CheckButtons();

  digitalWrite(column[11],HIGH);
  digitalWrite(column[12],HIGH);
  digitalWrite(column[11],LOW);
  digitalWrite(column[12],LOW);

  switch (hourFormat12()) {
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

  switch ((minute()/10)) {
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

  switch (minute()%10) {
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

void allOn(){
  for(int x=0;x<5;x++){
    for(int y=0;y<13;y++){
      digitalWrite(row[x],LOW);
      digitalWrite(column[y],HIGH);
    }
  }
}

void allOff(){
  for(int x=0;x<5;x++){
    for(int y=0;y<13;y++){
      digitalWrite(row[x],HIGH);
      digitalWrite(column[y],LOW);
    }
  }
}

void zero(int x){
  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[1],HIGH);

}

void one(int x){
  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[4],HIGH);
}

void two(int x){
  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[0],HIGH);

}

void three(int x){
  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[0],HIGH);

}

void four(int x){
  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[4],HIGH);
}

void five(int x){
  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[0],HIGH);

}

void six(int x){
  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[1],HIGH);

}

void seven(int x){
  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[4],HIGH);
}

void eight(int x){
  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[2],HIGH);

}

void nine(int x){
  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[0],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[0],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[1],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[1],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[1+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[1+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[2],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[2],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[3],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[3],HIGH);

  digitalWrite(column[2+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[2+x],LOW);
  digitalWrite(row[4],HIGH);

  digitalWrite(column[3+x],HIGH);
  digitalWrite(row[4],LOW);
  digitalWrite(column[3+x],LOW);
  digitalWrite(row[4],HIGH);


}

