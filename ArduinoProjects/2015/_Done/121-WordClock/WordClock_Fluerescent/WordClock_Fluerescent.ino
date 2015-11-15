#include <CUU_Interface.h>
#include <CUU_Parallel_I80.h>
#include <CUU_Parallel_M68.h>
#include <CUU_Serial.h>
#include <Noritake_VFD_CUU.h>
#include <util/delay.h>

//-- Word Clock --
String ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
String tens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
String tys[] = {"", "twenty", "half", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
String spaces = "                    "; // 20 spaces

char buffer[21];
int hour = 5;
int dly = 750;

String PrintWord(int num)
{
  String result = "";

  int onez = num % 10;
  int tenz = num / 10;

  if (tenz == 0)
    result = ones[onez];
  else if (tenz == 1)
    result = tens[onez];
  else result = tys[tenz - 1] + " " + ones[onez];

  return result;
}



// Uncomment one of the communication interfaces below.
CUU_Parallel_M68 interface(11, 12, 13, 3, 4, 5, 6, 7, 8, 9, 10); //RS,WR,RD,D0-D7
//CUU_Serial interface(3, 5, 6); // SIO, STB, SCK
//CUU_Parallel_I80 interface(9,10,11, 0,1,2,3,4,5,6,7); //RS,RW,E,D0-D7
//CUU_Parallel_I80_4bit interface(9,10,11, 4,5,6,7); //RS,RW,E,D4-D7
//CUU_Parallel_M68 interface(9,10,11, 0,1,2,3,4,5,6,7);//RS,WR,RD,D0-D7
//CUU_Parallel_M68_4bit interface(9,10,11, 4,5,6,7);//RS,WR,RD,D4-D7

Noritake_VFD_CUU vfd;

void setup() {
  _delay_ms(500);      // wait for device to power up
  vfd.begin(20, 2);    // 20x2 character module
  vfd.interface(interface); // select which interface to use

  // Uncomment if the target module supports brightness boost
  //vfd.brightnessBoost(); // module has brightness boost

  // Uncomment if model is DS2045G
  //vfd.bcVFD();          // is DS2045G

  vfd.CUU_init();      // initialize module
}

void loop() {
  
  //-- O'clock --
  vfd.CUU_clearScreen();
  PrintAt(0, PrintWord(hour) + " o'clock!");
  delay(dly);
  
  //-- Past X --
  vfd.CUU_clearScreen();
  PrintAt(1, String("past ") + PrintWord(hour));
  for (int minute = 1; minute <= 30; minute++) {
    PrintAt(0, PrintWord(minute));
    delay(dly);
  }
  
  //-- Till Y --
  vfd.CUU_clearScreen();
  PrintAt(1, "till " + PrintWord(hour+1));
  for (int minute = 29; minute >0; minute--) {
    PrintAt(0, PrintWord(minute));
    delay(dly);
  }

  hour++;
}

void PrintAt(int line, String text)
{
  vfd.CUU_setCursor(0,line);
  String padded = (text + spaces).substring(0,20);
  padded.toCharArray(buffer, 20);
  vfd.println( buffer );
}

