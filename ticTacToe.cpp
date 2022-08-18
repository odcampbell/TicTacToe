//Holds basic functions for playing a multiplayer game of Tic Tac Toe, and most functions
// called by main

#include <iostream>
#include <climits>
#include <vector>
#include<limits> //used to get numeric limits
#include "common.h"

using  namespace std;

//allocates mem for board (2d array) and initializes it
void MakeBoard(char** board){ 
     int i,j;

    //initilizes array with spaces
    for(i=0; i<3; i++){
        board[i] = new char[3];
    }

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            board[i][j] = ' ';
        }
    }
}

//Prints out global check vector, initally used to test vector for 
//functionality, TODO, adapt to show remaining spots on board
void PrintVector(){
    int i;
    for(i=0; i<9; i++){
        cout<<boardList[i]<<' ';
    }
    cout<<endl;
}

//Prints main game menu
void PrintMenu(){
    cout<<"   MENU"<< endl;
    cout<<"----------"<<endl;
    cout<<"1. Play A Multi Player Match"<<endl;
    cout<<"2. Play vs CPU"<<endl;
    cout<<"3. Play vs CPU (CPU Goes First)"<<endl;
    cout<<"4. Quit"<<endl;
    cout<<"Enter 1 - 4: ";
}


/*
  Code for User vs User Tic Tac Toe mode
 Gets user symbols, then loops through turns where each player chooses
 a spot on the board, after which a win condition is checked
 Game starts and ends in this function, It is called in main.cpp
*/
void UserVsUser(char** board){

    //Get Symbols
    char player1, player2;
    
    cout<<"Player 1, enter your symbol: ";
    player1 = GetPlayerSymbol(1);

    cout<<endl<<"Player 2, enter your symbol: ";
    player2 = GetPlayerSymbol(2, player1);

    cout<<"1 = "<<player1<<endl<<"2 = "<<player2<<endl;
    cout<<endl;

    players[0] = player1;
    players[1] = player2;

    PrintBoard(board);

    //Get position and place on board
    char userChoice;
    int tie = 0;
    bool boardSpot = false, win1 = false, win2 = false;
    
    while(1){

        //Player #1 choose spot, reloop on bad spot
        //TODO: might as well make a turn function - takes in board and int for user? 
        // cause of global symbol array?
        while (boardSpot != true){ 
           
            cout<<endl<<"Player #1, Choose a spot: "; 
            
            cin>> userChoice; 
            boardSpot = PlaceSymbol(player1,userChoice,board);

            if(boardSpot == false){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } 
            cout<<endl;
            PrintBoard(board);
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if((win1 = CheckWinCondition(player1,board))) break;
        
        tie++; //counts turns, can only tie after player 1
        if(tie == 9) break;

        boardSpot = false;
        //Player #2 choose spot, reloop on bad spot
        while (boardSpot != true){

            cout<<endl<<"Player #2, Choose a spot: "; 
            cin>> userChoice; 
            boardSpot = PlaceSymbol(player2, userChoice, board);
            if(boardSpot == false){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } 
            cout<<endl;
            PrintBoard(board);
        }

        if((win2 = CheckWinCondition(player2, board))) break;
        boardSpot = false;
        tie++;

    }

    if(win1) cout<<endl<< "Congrats Player #1, You Won!!" <<endl;
    else if(win2) cout<<endl<< "Congrats Player #2, You Won!!" <<endl;
    else if(tie == 9) cout<<endl<< "This match was a Tie!" <<endl;

}

//Sets global check vector back to 0's, and board back to spaces
// after a game is played
void ClearBoard(char** board){

    int i,j;

     //clear placement boardList
    for(i=0; i<9; i++){
        boardList.at(i) = 0;
    }

    //reset board to numerical place holders
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            board[i][j] = ' ';
        }
    }
}

//memory management
void FreeBoard(char** board ){

     int i;
    for(i=0; i<3; i++){
        delete[] board[i];
    }
    delete[] board;
}
