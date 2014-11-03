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
//  "***7**56*",
  "***7**561",
  "*81*49*26",
//"381*49726",
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
  
  Serial.println("SOLVED:");
  board.Print2();

  Serial.print("Board(1,2)=");
  Serial.println((board.GetCell(1,2))->Get());

  Serial.print("Board(1,3)=");
  Serial.println((board.GetCell(1,3))->Get());
}

void loop() {
}

