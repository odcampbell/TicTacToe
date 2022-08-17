#pragma once
//Holds functions and containers used in both TicTacToe.cpp and playCPU.cpp

#include <vector>

extern std::vector<int> boardList;
using namespace std;
extern char players[2]; //holds each players char after updated in main game fucntions


void PrintBoard(char **board);
void PrintPlacement();
char GetPlayerSymbol(int player, char player1Symbol ='O');
bool CheckPos(int userPosition);
bool PlaceSymbol(char symbol, char pos, char** board, bool vsCPU=false);
bool HorizonalWin(char symbol, char** board);
bool VerticalWin(char symbol,char** board);
bool CheckWinCondition(char symbol, char** board);
int AllWinConditions(char** board);
bool DiagonalWin(char symbol,char** board);
void SwapUsers();