//Holds functions and containers used in both TicTacToe.cpp and playCPU.cpp

#include <iostream>
#include <vector>
#include "playCPU.h"

using  namespace std;

char players[2] = {'0','0'}; //holds each players char after updated in main game fucntions
vector<int> boardList(9,0);

/*Prints the board in its current state with characters in the positions 
  chosen by the user or cpu
  Used any time the board is updated, and also at the start of a game,
  Takes in a 2-d array 
  See UserVsUser, CPUGoesFirst, PlayVsCPU functions
*/
void PrintBoard(char **board){
    int i,j;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(j==0 || j==1) cout<< board[i][j] << " | ";
            else cout<< board[i][j];     
        }
        cout<<endl;

        //only prints two horizontal lines
        if(i<=1){
            for(j=0; j<3; j++){
                cout<< "---";
            }
            cout<<endl;
        }
    }
}

/*Prints placement of numbers (0-8) on board that users can enter
  when choosing a spot (which maps to board via switch statement)
  made this as an easy function for seeing the number spots since they're no longer
  place holders for the array, now the array starts off empty
*/
void PrintPlacement(){
    int i,j,k=0;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(j==0 || j==1) cout<< k << " | ";
            else cout<< k; 

            k++;    
        }
        cout<<endl;

        //only prints two horizontal lines
        if(i<=1){
            for(j=0; j<3; j++){
                cout<< "---";
            }
            cout<<endl;
        }
    }
}

//Gets symbols for users to put on board and returns them
//Takes in an int = 1 for player 1, or 2 for player 2
//For the second player, pass in player one's symbol to ensure they're unique
char GetPlayerSymbol(int player, char player1Symbol ='O'){ //WORKS
    //make var and save user input
    char symbol;
    cin>> symbol;
    while(1){

        if((player == 2) && (symbol == player1Symbol)){
            cout<<endl;
            cout<<"Choose a different symbol than player 1!"<<endl <<"Player 2: ";
        }
        else break;

        cin>> symbol;
    }
    
    cin.ignore(10000,'\n');
    return symbol;
}

/* Checks whether there is a 0 or 1 in the user's selected position (0-8) in
  the global vector. If there is a 0, then the spot is open so the user can 
  place their symbol there. 
  Returns boolean value, true for open spots, false for filled spot
*/
bool CheckPos(int userPosition){
    bool checker = true;
    if(boardList.at(userPosition) == 1) checker = false;
    return checker;
}

//Wrapper unction used to swap players symbols in the global players array which
// stores user symbols. Needed this function to use the minimax algorithim
// for hints. At least it was the easiest method for my configuration
void SwapUsers(){
    swap(players[0],players[1]);  
}

  /*Uses a switch statement to place a symbol at a specific spot on the board
   could refactor to look like the CPU Place Symbol function by typcasting
   the user's position before entering it as an argument
   If the CheckPos function returns false, then no symbol is placed
   Takes in a boolean variable to control whether hints are available
  */
bool PlaceSymbol(char symbol, char pos, char** board, bool vsCPU=false){
    
    bool check = false;
    int pos1 = 0;
    int hint = 0;
    switch(pos){
        case '0':
            pos1 = 0;
            if((check = CheckPos(pos1))){
                board[0][0] = symbol;
                boardList.at(pos1) = 1;
            }
            else cout<<"This spot: "<< pos1<<" is taken."<<endl;
            break;

        case '1':
            pos1 = 1;
            if((check = CheckPos(pos1))){
                board[0][1] = symbol;
                boardList.at(pos1) = 1;
            }
            else cout<<"This spot: "<< pos1<<" is taken."<<endl;
            break;

        case '2':
            pos1 = 2;
            if((check = CheckPos(pos1))){
                board[0][2] = symbol;
                boardList.at(pos1) = 1;
            }
            else cout<<"This spot: "<< pos1<<" is taken."<<endl;
            break;

        case '3':
            pos1 = 3;
            if((check = CheckPos(pos1))){
                board[1][0] = symbol;
                boardList.at(pos1) = 1;
            }
            else cout<<"This spot: "<< pos1<<" is taken."<<endl;
            break;

        case '4':
            pos1 = 4;
            if((check = CheckPos(pos1))){
                board[1][1] = symbol;
                boardList.at(pos1) = 1;
            }
            else cout<<"This spot: "<< pos1<<" is taken."<<endl;
            break;

        case '5':
            pos1 = 5;
            if((check = CheckPos(pos1))){
                board[1][2] = symbol;
                boardList.at(pos1) = 1;
            }
            else cout<<"This spot: "<< pos1<<" is taken."<<endl;
            break;

        case '6':
            pos1 = 6;
            if((check = CheckPos(pos1))){
                board[2][0] = symbol;
                boardList.at(pos1) = 1;
            }
            else cout<<"This spot: "<< pos1<<" is taken."<<endl;
            break;

        case '7':
            pos1 = 7;
            if((check = CheckPos(pos1))){
                board[2][1] = symbol;
                boardList.at(pos1) = 1;
            }
            else cout<<"This spot: "<< pos1<<" is taken."<<endl;
            break;

        case '8':
            pos1 = 8;
            if((check = CheckPos(pos1))){
                board[2][2] = symbol;
                boardList.at(pos1) = 1;
            }
            else cout<<"This spot: "<< pos1<<" is taken."<<endl;
            break;

        case '9':
            if(vsCPU == false){
                cout<<"Error! Pick a valid board placement (0-8)"<<endl;
                break;
            }

            //If playing cpu, swap symbols temporarily to make minimax function work for you!
            SwapUsers();
            hint = FindCpuSpot(symbol,board,false);
            cout<< "Try this spot: "<<hint<<endl;
            SwapUsers();
            break;

        default:
            cout<<"Error! Pick a valid board placement (0-8)"<<endl;
    }
   
   return check;
}

//Loops through entire board (2d array), checks if any row has three of 
// a user's symbols, then sets a boolean flag accordingly
bool HorizonalWin(char symbol, char** board){ //WORKS
    int i,j, win = 0;
    bool winCond = false;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(board[i][j] == symbol){
                win++;
            }
            else win = 0;
        }
        if(win == 3) winCond = true;
        win=0;
    }
    return winCond;
}

//Loops through entire board (2d array) and checks to see if any column
// has three of a user's symbols, then sets a boolean flag accordingly
bool VerticalWin(char symbol,char** board){
    int i,j;
    int win1 = 0,win2 = 0,win3 = 0;
    bool winCond = false;
    //i=rows
    //j=cols
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){

            //col 0
            if(j == 0){
                if(board[i][j] == symbol) win1++;
            } 

            //col 1
            if(j == 1){
                if(board[i][j] == symbol) win2++;
            } 

            //col 2
            if(j == 2){
                if(board[i][j] == symbol) win3++;
            } 
        }
    }

    if(win1 == 3 || win2 == 3 || win3 == 3) winCond = true;

    return winCond;
}

/*
Hard coded a check for each diagonal spot in 2d array, returns boolean
 if user has 3 symbols ina row
 Since I started my board at 0 instead of 1, I believe I through off potential 
 to us a different means of checking via modulo 
 */
bool DiagonalWin(char symbol,char** board){
    int win = 0;
    bool winCond = false;
    if((board[0][0] == symbol) && (board[1][1] == symbol) && (board[2][2] == symbol)) win = 3;
    if((board[0][2] == symbol) && (board[1][1] == symbol) && (board[2][0] == symbol)) win = 3;
    if(win == 3) winCond = true;

    return winCond;
}

//Checks to see if player with the given symbol has three of them in a row
// vertically, horizontally, or diagonally,
//Used to signal that someone has won the game and to exit the game being played
bool CheckWinCondition(char symbol, char** board){
    bool winCond = false;
    if(HorizonalWin(symbol,board) == true) winCond = true; 
    if(VerticalWin(symbol,board) == true) winCond = true;
    if(DiagonalWin(symbol,board) == true) winCond = true;

    return winCond;
}

//Checks to see if either player won, if there's at tie, or if the match is still going
//returns 1 for player 1, 2 for player 2 or CP, 3 for tie, and 4 for no win yet
//added this code really to help with the minimax function which needed to know the games state
int AllWinConditions(char** board){
    bool win1,win2;
    int openSpots = 0;

    win1 = CheckWinCondition(players[0],board);//user
    win2 = CheckWinCondition(players[1],board); //computer

    int i,j;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(board[i][j] ==' ') openSpots++;
        }
    }

    if(win1){
        return 1;
    }
    else if(win2){
        return 2;
    }
    else if(openSpots == 0){
        return 3;
    }
    return 4; //if no winner yet
}

