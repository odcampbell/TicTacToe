#include <iostream>
#include <vector>
#include "playCPU.h"

using  namespace std;

char players[2]={'0','0'}; //holds each players char after updated in main game fucntions
vector<int> boardList(9,0);

//Print current board after user move
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

//prints placement of nubmers on board,
//made this as an easy function for seeing the number spots since they're noo longer
//place holders for the array FIXME: need a print remaining spots option, ofc people can see the board
//but its just a small quality of life improvement to know what spots are left
//could also use minimax algorithim to suggest hint on best move to user! with an option to see the hint or not
// before choosing their spot what if it results in a tie?? tell user if they want to see hint
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

//Called two times to get symbols
//second time, pass in player one's symbol to make sure player 2 doesn't equal 1
// or called one time to only get player1's symbol (when playing CPU, who's hard coded)
char GetPlayerSymbol(int player, char player1Symbol ='O'){ //WORKS
    //make var and save user input
    char symbol;
    cin>> symbol;
    while(1){
            //if on second user, make sure it odesnt equal the first
        if((player == 2) && (symbol == player1Symbol)){
            cout<<endl;
            cout<<"Choose a different symbol than player 1!"<<endl <<"Player 2: ";
        }
        else break;

        cin>> symbol;
    }
    //cin.clear();
    cin.ignore(10000,'\n');
    return symbol;
}


/*Because I initially had the board full of numbers, and allowed numbers as character inputs
  It was easier to just use a 0-8 check box (the vector) to know if a spot was open in the board
  or not, after having changed the board to only being filled with ' ' spaces, Im not sure
  what the practical use of og having a vector for this function really is,
 it is somewhat cleaner than having a switch statement and if statment for each spot on the board
  so I think Ill leave it in its configuration, obviously whenever the board is changed tho, you must be sure to update the vector
  or this function would lead to logic errors
*/
bool CheckPos(int userPosition){ //works!
    bool checker = true;
    if(boardList.at(userPosition) == 1) checker = false;
    return checker;
}

void SwapUsers(){
    char temp;
    temp = players[1];
    players[1]=players[0];
    players[0]=temp;
   
}
  //uses a switch statement to place a symbol at a specific spot on the board
  //could refactor to not have to do the symbol change thing (would look more like the cpuPlaceSymbol)
  //function, but would have to type convert the input prior
bool PlaceSymbol(char symbol, char pos, char** board, bool vsCPU=false){ //works!
    
    bool check = false;
    int pos1=0;
    int hint=0;
    switch(pos){
        case '0':
            pos1=0;
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
            SwapUsers();
            hint = FindCpuSpot(symbol,board,false);
            cout<< "Try this spot: "<<hint<<endl;
            SwapUsers();
            break;

        default:
            cout<<"Error! Pick a valid board placement (0-8)"<<endl;
    }
    //board is initialized w/ 0-8, if a space isnt 0-8, it's used
   return check;
}

//Loops through entire board, checks if win var = 3 for each row
// increments that var every time it finds the symbol, sets a boolean flag 
//if it has 3 in a row
bool HorizonalWin(char symbol, char** board){ //WORKS
    int i,j, win=0;
    bool winCond = false;
    //i=rows
    //j=cols
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(board[i][j] == symbol){
                win++;
            }
            else win=0;//not needed?
        }
        if(win == 3) winCond=true;
        win=0;
    }
    return winCond;
}

//Loops through entire board, keeps count var for each col, 
//if any of them = 3, return true
bool VerticalWin(char symbol,char** board){
    int i,j;
    int win1=0,win2=0,win3=0;
    bool winCond = false;
    //i=rows
    //j=cols
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){

            //col 0
            if(j==0){
                if(board[i][j] == symbol) win1++;
            } 

            //col 1
            if(j==1){
                if(board[i][j] == symbol) win2++;
            } 

            //col 2
            if(j==2){
                if(board[i][j] == symbol) win3++;
            } 
        }
    }

    if(win1 == 3 || win2 == 3 || win3 == 3) winCond=true;

    return winCond;
}

/*Since I started my board at 0 instead of 1, I believe I through off potential 
  to us a better means of checking via modulo, so I hard coded it instead
*/
bool DiagonalWin(char symbol,char** board){
    int win =0;
    bool winCond = false;
    if((board[0][0] == symbol) && (board[1][1] == symbol) && (board[2][2] == symbol)) win = 3;
    if((board[0][2] == symbol) && (board[1][1] == symbol) && (board[2][0] == symbol)) win = 3;
    if(win==3) winCond = true;

    return winCond;
}

//Checks to see if player with the given symbol has three of them in a row
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
    int openSpots=0;

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

