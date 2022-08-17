//Holds functions used primarily for playing the CPU

#include <iostream>
#include <vector>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#include "windows.h" //used for sleep function
#include "common.h"
using  namespace std;

//Places cpu symbol on board, used for that and temporarally using Minimax
void CpuPlaceSymbol(char symbol, int pos, char**board){

    switch(pos){
        case 0:
            board[0][0] = symbol;
            boardList.at(pos) = 1;
            break;

        case 1:
            board[0][1] = symbol;
            boardList.at(pos) = 1;
            break;

        case 2:
         
            board[0][2] = symbol;
            boardList.at(pos) = 1;
            break;

        case 3:
          
            board[1][0] = symbol;
            boardList.at(pos) = 1;
            break;

        case 4:

            board[1][1] = symbol;
            boardList.at(pos) = 1;
            break;

        case 5:
        
            board[1][2] = symbol;
            boardList.at(pos) = 1;
            break;

        case 6:
          
            board[2][0] = symbol;
            boardList.at(pos) = 1;
            break;

        case 7:

            board[2][1] = symbol;
            boardList.at(pos) = 1;
            break;

        case 8:

            board[2][2] = symbol;
            boardList.at(pos) = 1;
            break;
    }
}

//Resets board and boardList(global vector) at the given position, made as a helper cpu to use Minimax
// After cpu symbol is placed in an open spot, temporarily to test subsequent game
//states, this function removes it, making for cleaner associated minimax functions
void RemoveSymbol(int pos, char**board){

    switch(pos){
        case 0:
            board[0][0] = ' ';
            boardList.at(pos) = 0;
            break;

        case 1:
            board[0][1] = ' ';
            boardList.at(pos) = 0;
            break;

        case 2:
         
            board[0][2] = ' ';
            boardList.at(pos) = 0;
            break;

        case 3:
          
            board[1][0] = ' ';
            boardList.at(pos) = 0;
            break;

        case 4:

            board[1][1] = ' ';
            boardList.at(pos) = 0;
            break;

        case 5:
        
            board[1][2] = ' ';
            boardList.at(pos) = 0;
            break;

        case 6:
          
            board[2][0] = ' ';
            boardList.at(pos) = 0;
            break;

        case 7:

            board[2][1] = ' ';
            boardList.at(pos) = 0;
            break;

        case 8:

            board[2][2] = ' ';
            boardList.at(pos) = 0;
            break;
    }
}

//After the MiniMax function runs for a particular board placement, it returns
// a positive number, negative number, or 0
// based on the outcome of the game (if played from that point)
// This function represents and returns those end states as 0, 1, -1
int MiniMaxCond(int winCond){
    int minMaxVal = 0;
    switch(winCond){
        case 1:
            minMaxVal = -1;
            //user won, minimizing so -1
            break;

        case 2:
            minMaxVal = 1;
            // cpu won, maximizing so +1
            break;

        case 3:
            minMaxVal = 0;
            //it was a tie
            break;
        }

    return minMaxVal;
}

/*Allows for playing CPU 
 Recursively allows CPU to test the possible remaining game outcomes,
 Returns the outcome whenever a game is over, keeps track of the best one to return
 Only gets the best score from the current board, so a parent function 
 (FindCPUSpot) calls this for every remaining spot on the actual board
 (didnt need bool actually, not really accounting for 
 depth so cp wont always take insta win, but may take double win next turn)
*/
int MiniMax(char** board, int depth, bool isMaximizing){
    //Terminating Case: There are no more moves to make due to a win or a tie
    int result = AllWinConditions(board);
    if(result != 4){
        int scoreTemp = MiniMaxCond(result);
        return scoreTemp;
    }
    
    if(isMaximizing){
        
        int i,score = 0;
        int cpuSpot = 0;
        int bestScore = -10000000;
        //int bestSpot = 0;

        for(i=0; i<9; i++){
            //if open spot
            if(CheckPos(i)){
                cpuSpot = i;
                CpuPlaceSymbol(players[1], cpuSpot, board);
                score = MiniMax(board, depth+1, false);
                RemoveSymbol(cpuSpot, board);

                if (score > bestScore){
                    bestScore = score;
                }
            }
        }
        return bestScore;
    }
    else{
        int i,score;
        int spot = 0;
        int bestScore = 10000000;

        for(i=0; i<9; i++){
            //if open spot
            if(CheckPos(i)){
                spot = i;
                CpuPlaceSymbol(players[0], spot, board);
                score = MiniMax(board, depth+1, true);
                RemoveSymbol(spot, board);

                if (score < bestScore){
                    bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

//Calls MiniMax function for each remaining spot on the board,
//keeps track of best score and corresponding best spot 
// returns best spot
 int FindCpuSpot(char cpuSymbol, char**board,bool turn){
    int i,score;
    bool spot = false;
    int cpuSpot = 0;
    int bestScore = -100000000;
    int bestSpot = 0;


    for(i=0; i<9; i++){
        spot = CheckPos(i);
        if(spot){
            cpuSpot = i;
            CpuPlaceSymbol(cpuSymbol, cpuSpot, board);
            score = MiniMax(board, 0, turn);
            RemoveSymbol(cpuSpot, board);

            if(score > bestScore){
                bestScore = score;
                bestSpot = cpuSpot;
            }
        }
    }
    return bestSpot;
}

//Code for playing CPU Tic Tac Toe where CPU goes second 
//supports using minimax for hints
//see Player VS Player function for more info
void PlayVsCp(char** board){

      //Get Symbols
    char player1, cpuPlayer;
    
    cout<<"Player 1, enter your symbol: ";
    player1 = GetPlayerSymbol(1);
    
    if(player1 == 'O' || player1 =='o' || player1 == '0' || player1 == 'Q') cpuPlayer = 'X';
    else cpuPlayer = 'O';
    
    //update global string for MiniMax function to chekc win condition
    players[0] = player1;
    players[1] = cpuPlayer;

    cout<<"Player 1 = "< <players[0] <<endl<< "CPU = " << players[1] <<endl;
    cout<<endl;

    PrintBoard(board);

      //Get position and place on board
    char userChoice, cpuChoice;
    int tie = 0;
    bool boardSpot = false, win1 = false, win2 = false;
    
    while(1){

        //Break on tie why here??
        if(tie == 9) break;

        //Player #1 choose spot, reloop on bad spot
        while (boardSpot != true){

            cout<<endl<<"Player #1, Choose a spot, or choose '9' for a hint: "; 
            cin>> userChoice; 
            boardSpot = PlaceSymbol(player1,userChoice,board,true);

            if(boardSpot == false){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } 
            cout<<endl;
            PrintBoard(board);
        }

        
        if((win1 = CheckWinCondition(player1,board))) break;
        tie++;

        if(tie == 9) break;

        boardSpot = false;
        //Player #2 choose spot, reloop on bad spot

        cout<<endl<<"CPU is choosing a spot: "; 
        
        cpuChoice = FindCpuSpot(cpuPlayer, board, false);
        CpuPlaceSymbol(cpuPlayer, cpuChoice, board);
        
        cout<<endl;
        Sleep(900);
        PrintBoard(board);


        if((win2 = CheckWinCondition(cpuPlayer, board))) break;
        
        tie++;
    }
    if(win1) cout<<endl<< "Congrats Player #1, You Won!!" <<endl;
    else if(win2) cout<<endl<< "Congrats CPU, You Won!!" <<endl;
    else if(tie == 9) cout<<endl<< "This match was a Tie!" <<endl;

}

//Code for playing CPU Tic Tac Toe where CPU goes first
//Supports using minimax for hints
//see Player VS Player function for more info
void CpuGoesFirst(char** board){

      //Get Symbols //changed player2 to player in this context makes more sense
    char player, cpuPlayer;
    
    cout<<"Player, enter your symbol: ";
    player = GetPlayerSymbol(1);
    
    if(player == 'O' || player =='o' || player == '0' || player == 'Q') cpuPlayer = 'X';
    else cpuPlayer = 'O';
    
    //update global string for MiniMax function to chekc win condition
    players[0] = player;
    players[1] = cpuPlayer;

    cout<<"CPU = "<<players[1]<<endl<<"Player = "<<players[0]<<endl;
    cout<<endl;

    PrintBoard(board);

      //Get position and place on board
    char userChoice, cpuChoice;
    int tie = 0;
    bool boardSpot = false, win1 = false, win2 = false;
    
    while(1){
        if(tie == 9) break;

        //Player #1 choose spot, reloop on bad spot
        cout<<endl<< "CPU is choosing a spot: "; 
        cpuChoice = FindCpuSpot(cpuPlayer, board, false);
        CpuPlaceSymbol(cpuPlayer, cpuChoice, board);
        cout<<endl;
        Sleep(900);
        PrintBoard(board);

        if((win2 = CheckWinCondition(cpuPlayer, board))) break;
        tie++;

        //Break on tie
        if(tie == 9) break;

        boardSpot = false;
        //Player #2 choose spot, reloop on bad spot
        while (boardSpot != true){
            
            cout<<endl<<"Player #2, Choose a spot, or choose '9' for a hint: ";
            cin>> userChoice; 
           
            boardSpot = PlaceSymbol(player,userChoice,board,true);

            if(boardSpot == false){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } 
            cout<<endl;
            PrintBoard(board);
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if((win1 = CheckWinCondition(player,board))) break;
        tie++;
 
    }
    if(win1) cout<<endl<< "Congrats Player #2, You Won!!" <<endl;
    else if(win2) cout<<endl<< "Congrats CPU, You Won!!" <<endl;
    else if(tie == 9) cout<<endl<< "This match was a Tie!" <<endl;

}
