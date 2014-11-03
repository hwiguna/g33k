#include "Arduino.h"
#include "Debug.h"
#include "Board.h"
#include "Scanner.h"

Debug debug;
Board board(debug);
Scanner scanner(debug, &board);

char* puzzle[] = {
  "*****5347",
  "*564*12**",
  "***7**56*",
//"***7**561", // Test2
  "*81*49*26",
//"381*49726", // Test1
  "**7***9**",
  "****2***4",
  "**8356**2",
  "54**7**19",
  "**2****5*"
};

void setup() {
  // initialize serial:
  Serial.begin(57600); //
  
  Serial.println("Puzzle:");
  board.Init(puzzle);
  board.Print();

  Serial.println("Solving...");
  scanner.Solve();
  
  Serial.println();
  Serial.println("SOLVED:");
  board.Print2();

  Serial.println("DONE!");
}

void loop() {
}

