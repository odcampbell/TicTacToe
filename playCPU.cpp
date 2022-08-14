#include <iostream>
#include <vector>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#include "windows.h" //used for sleep function
#include "common.h"
using  namespace std;

//Places cpu symbol on board, used for that and temporarally using Minimax
void cpuPlaceSymbol(char symbol, int pos, char**board){

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

//Resets board and boardList at position, for cpu to use Minimax 
void removeSymbol(int pos, char**board){

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

int miniMaxCond(int winCond){
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

//allows playing AI, didnt need bool actually, not really accounting for 
//depth so cp wont always take insta win, but may take double win next turn
int minimax(char** board, int depth, bool isMaximizing){
    //Terminating Case: There are no more moves to make due to a win or a tie
    int result = allWinConditions(board);
    if(result != 4){
        int scoreTemp = miniMaxCond(result);
        return scoreTemp;
    }
    
    if(isMaximizing){
        
        int i,score=0;
        int cpuSpot = 0;
        int bestScore=-10000000;
        //int bestSpot = 0;

        for(i=0; i<9; i++){
            //if open spot
            if(checkPos(i)){
                cpuSpot = i;
                cpuPlaceSymbol(players[1],cpuSpot,board);
                score = minimax(board,depth+1,false);
                removeSymbol(cpuSpot,board);

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
        int bestScore=10000000;

        for(i=0; i<9; i++){
            //if open spot
            if(checkPos(i)){
                spot = i;
                cpuPlaceSymbol(players[0],spot,board);
                score = minimax(board,depth+1,true);
                removeSymbol(spot,board);

                if (score < bestScore){
                    bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

 int findCpuSpot(char cpuSymbol, char**board,bool turn){
    int i,score;
    bool spot = false;
    int cpuSpot = 0;
    int bestScore= -100000000;
    int bestSpot = 0;


    for(i=0; i<9; i++){
        spot = checkPos(i);
        if(spot){
            cpuSpot = i;
            cpuPlaceSymbol(cpuSymbol,cpuSpot,board);
            score = minimax(board,0,turn);
            removeSymbol(cpuSpot,board);

            if(score > bestScore){
                bestScore = score;
                bestSpot = cpuSpot;
            }
        }
    }
    return bestSpot;
}

//code for playing CP Tic Tac Toe where cp goes second
void playVsCp(char** board){

      //Get Symbols
    char player1, cpuPlayer;
    
    cout<<"Player 1, enter your symbol: ";
    player1 = getPlayerSymbol(1);
    
    if(player1 == 'O' || player1 =='o' || player1 == '0' || player1 == 'Q') cpuPlayer = 'X';
    else cpuPlayer = 'O';
    
    //update global string for minimax function to chekc win condition
    players[0] = player1;
    players[1] = cpuPlayer;

    cout<<"Player 1 = "<<players[0]<<endl<<"CPU = "<<players[1]<<endl;
    cout<<endl;

    printBoard(board);

      //Get position and place on board
    char userChoice, cpuChoice;
    int tie=0;
    bool boardSpot=false, win1= false,win2=false;
    
    while(1){

        //Break on tie why here??
        if(tie==9) break;

        //Player #1 choose spot, reloop on bad spot
        while (boardSpot!=true){

            cout<<endl<<"Player #1, Choose a spot, or choose '9' for a hint: "; 
            cin>> userChoice; 
            boardSpot = placeSymbol(player1,userChoice,board,true);

            if(boardSpot == false){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } 
            cout<<endl;
            printBoard(board);
        }

        
        if((win1=checkWinCondition(player1,board))) break;
        tie++;

        if(tie==9) break;

        boardSpot = false;
        //Player #2 choose spot, reloop on bad spot

        cout<<endl<<"CPU is choosing a spot: "; 
        
        cpuChoice = findCpuSpot(cpuPlayer,board,false);
        cpuPlaceSymbol(cpuPlayer,cpuChoice,board);
        
        cout<<endl;
        Sleep(900);
        printBoard(board);


        if((win2=checkWinCondition(cpuPlayer,board))) break;
        
        tie++;
    }
    if(win1) cout<<endl<<"Congrats Player #1, You Won!!"<<endl;
    else if(win2) cout<<endl<<"Congrats CPU, You Won!!"<<endl;
    else if(tie==9) cout<<endl<<"This match was a Tie!"<<endl;

}

void cpuGoesFirst(char** board){

      //Get Symbols //changed player2 to player in this context makes more sense
    char player, cpuPlayer;
    
    cout<<"Player, enter your symbol: ";
    player = getPlayerSymbol(1);
    
    if(player == 'O' || player =='o' || player == '0' || player == 'Q') cpuPlayer = 'X';
    else cpuPlayer = 'O';
    
    //update global string for minimax function to chekc win condition
    players[0] = player;
    players[1] = cpuPlayer;

    cout<<"CPU = "<<players[1]<<endl<<"Player = "<<players[0]<<endl;
    cout<<endl;

    printBoard(board);

      //Get position and place on board
    char userChoice, cpuChoice;
    int tie=0;
    bool boardSpot=false, win1= false,win2=false;
    
    while(1){
        if(tie==9) break;

        //Player #1 choose spot, reloop on bad spot
        cout<<endl<<"CPU is choosing a spot: "; 
        cpuChoice = findCpuSpot(cpuPlayer,board,false);
        cpuPlaceSymbol(cpuPlayer,cpuChoice,board);
        cout<<endl;
        Sleep(900);
        printBoard(board);

        if((win2=checkWinCondition(cpuPlayer,board))) break;
        tie++;

        //Break on tie
        if(tie==9) break;

        boardSpot = false;
        //Player #2 choose spot, reloop on bad spot
        while (boardSpot!=true){
            
            cout<<endl<<"Player #2, Choose a spot, or choose '9' for a hint: ";
            cin>> userChoice; 
           
            boardSpot = placeSymbol(player,userChoice,board,true);

            if(boardSpot == false){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } 
            cout<<endl;
            printBoard(board);
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if((win1=checkWinCondition(player,board))) break;
        tie++;
 
    }
    if(win1) cout<<endl<<"Congrats Player #2, You Won!!"<<endl;
    else if(win2) cout<<endl<<"Congrats CPU, You Won!!"<<endl;
    else if(tie==9) cout<<endl<<"This match was a Tie!"<<endl;

}
