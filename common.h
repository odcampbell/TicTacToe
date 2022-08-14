#pragma once

#include <vector>

extern std::vector<int> boardList;
using namespace std;
extern char players[2]; //holds each players char after updated in main game fucntions


void printBoard(char **board);
void printPlacement();
char getPlayerSymbol(int player, char player1Symbol ='O');
bool checkPos(int userPosition);
bool placeSymbol(char symbol, char pos, char** board, bool vsCPU=false);
bool horizonalWin(char symbol, char** board);
bool verticalWin(char symbol,char** board);
bool checkWinCondition(char symbol, char** board);
int allWinConditions(char** board);
bool diagonalWin(char symbol,char** board);
void swapUsers();