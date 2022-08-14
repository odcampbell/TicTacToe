#pragma once

void playVsCp(char** board);
int findCpuSpot(char cpuSymbol, char**board, bool turn);
int minimax(char** board, int depth, bool isMaximizing);
int miniMaxCond(int winCond);
void removeSymbol(int pos, char**board);
void cpuPlaceSymbol(char symbol, int pos, char**board);
void cpuGoesFirst(char** board);
