#include "Arduino.h"
#include "Debug.h"
#include "Board.h"
#include "Pattern.h"
#include "PatternList.h"
#include "Scanner.h"

Debug debug;
Board board(debug);
Scanner scanner(debug, &board);

char* puzzle[] = {
  "5....9...",
  "..7..1...",
  ".4.6..38.",
  "..8..5...",
  "2...374..",
  "..51..2..",
  "79....135",
  "..4......",
  "..6..3.2.",
};

void setup() {
  Serial.begin(57600);
  
  Serial.println("Puzzle:");
  board.Init(puzzle);
  board.Print();

  Serial.println("Solving...");
  scanner.Solve();
  
  Serial.println();
  Serial.println("SOLUTION:");
  board.Print2();

  Serial.println("DONE!");
}

void loop() {
}

/*
-- Empty
char* puzzle[] = {
  ".........",
  ".........",
  ".........",
  ".........",
  ".........",
  ".........",
  ".........",
  ".........",
  ".........",
};

-- Medium 1
char* puzzle[] = {
  ".7..9..53",
  "...4..7..",
  ".2...5...",
  "...3.....",
  "...8.2469",
  ".1...6.2.",
  "1........",
  "...9....5",
  "85....63.",
};

-- Medium 2
char* puzzle[] = {
  "5....9...",
  "..7..1...",
  ".4.6..38.",
  "..8..5...",
  "2...374..",
  "..51..2..",
  "79....135",
  "..4......",
  "..6..3.2.",
};

-- Very Easy 1
char* puzzle[] = {
  ".....5347",
  ".564.12..",
  "...7..56.",
  ".81.49.26",
  "..7...9..",
  "....2...4",
  "..8356..2",
  "54..7..19",
  "..2....5."
};

-- Very Easy 2
char* puzzle[] = {
  ".4..791..",
  "...3..97.",
  "..9.6183.",
  ".....4.5.",
  "..12.6.4.",
  "4.6735..8",
  "......5..",
  "16.5.3...",
  "2.364.7..",
};
*/
