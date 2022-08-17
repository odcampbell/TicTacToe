#pragma once

//Holds functions used primarily for playing the CPU

void PlayVsCp(char** board);
int FindCpuSpot(char cpuSymbol, char**board, bool turn);
int MiniMax(char** board, int depth, bool isMaximizing);
int MiniMaxCond(int winCond);
void RemoveSymbol(int pos, char**board);
void CpuPlaceSymbol(char symbol, int pos, char**board);
void CpuGoesFirst(char** board);
