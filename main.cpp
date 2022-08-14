#include <iostream>
#include <limits>
#include "ticTacToe.h"
#include "common.h"
#include "playCPU.h"

using  namespace std;

int main(){
    
    //Base declarations
    int userSelection = 0; //play game or quit
    char** gameBoard;  //2d array 
    bool validSelection = true;
    gameBoard = new char*[3]; 
    MakeBoard(gameBoard); //set mem and initialize 0-8
    
    while(1){

        //didnt want to use another while loop to but needed to manage print
        //didnt want to repeatedly print board and menu for every bad input
        if(validSelection){ 

            //start of new match
            cout<<"Here's a Clean Board"<<endl;
            PrintPlacement();
            cout<<endl;
            PrintMenu();

             if (!(cin >> userSelection)) { //input verification
                cout << "Please enter numbers only." << endl;
                cin.clear();
                cin.ignore(10000,'\n');
            }
            cout<<endl;
        }
        else{ 
            //routes here on any bad inputs after, previous if statement only runs once per new match (selection)
                //successfully reduces print statements and checks input
         
            if (!(cin >> userSelection)) { //input verification
                cout << "Please enter numbers only." << endl;
                cin.clear();
                cin.ignore(10000,'\n');
            }
            cout<<endl;
            validSelection = true;
        }


        //plays one game
        if(userSelection == 1){
            cout<< endl <<"Let's play!"<<endl<< endl;
            cin.ignore(10000,'\n');
            UserVsUser(gameBoard); 
            ClearBoard(gameBoard);
            cout<<endl;
        }
        else if(userSelection == 2){
            cout<< endl <<"Playing CPU! You go first!"<<endl<< endl;

            PlayVsCp(gameBoard);
            ClearBoard(gameBoard);
            cout<<endl;
        }
        else if(userSelection == 3){
            cout<< endl <<"Playing CPU! And CPU goes First!"<<endl<< endl;

            CpuGoesFirst(gameBoard); 
            ClearBoard(gameBoard);
            cout<<endl;
        }
        else if (userSelection == 4){
            cout << "Exiting The Game! Thanks For Playing!";
            break;
        }
        else{
            cout<< "Invalid Option! Choose 1-4:";
            validSelection = false; //fixed menu selection error
        }

    }

    FreeBoard(gameBoard);

    return 0;
}