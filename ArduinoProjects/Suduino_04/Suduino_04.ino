#include "Arduino.h"
#include "Debug.h"
#include "Board.h"
#include "Scanner.h"

Debug debug;
Board board(debug);
Scanner scanner(debug, &board);

char* puzzle[] = {
  "*****5389",
  "*564*12**",
  "***7**56*",
//"*81*49*26",
  "381*49726",
  "**7***9**",
  "****2***4",
  "**8356**2",
  "54**7**19",
  "**2****5*"
};

//char puzzle[][9] = {
//  {'*','*','*', '*','*','5', '3','4','7'},
//  {'*','5','6', '4','*','1', '2','*','*'},
//  {'*','*','*', '7','*','*', '5','6','*'},
////{'*','8','1', '*','4','9', '*','2','6'},
//  {'3','8','1', '*','4','9', '7','2','6'},
//  {'*','*','7', '*','*','*', '9','*','*'},
//  {'*','*','*', '*','2','*', '*','*','4'},
//  {'*','*','8', '3','5','6', '*','*','2'},
//  {'5','4','*', '*','7','*', '*','1','9'},
//  {'*','*','2', '*','*','*', '*','5','*'}
//};

void setup() {
  // initialize serial:
  Serial.begin(9600);
  
  Serial.println("Puzzle:");
  board.Init(puzzle);
  board.Print();

  Serial.println("Solving...");
  scanner.Solve();
  
  Serial.println("SOLVED:");
  board.Print();

  Serial.print("Board(1,2)=");
  Serial.println((board.GetCell(1,2)).Get());

  Serial.print("Board(1,3)=");
  Serial.println((board.GetCell(1,3)).Get());
}

void loop() {
}

