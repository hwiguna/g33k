#include "Arduino.h"
#include "Debug.h"
#include "Board.h"
#include "Scanner.h"

Debug debug;
Board board(debug);
Scanner scanner(debug, &board);

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

void setup() {
  Serial.begin(57600);
  
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


char* puzzle_medium[] = {
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

