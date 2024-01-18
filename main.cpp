/**
 * @file main.cpp
 * @author Jordan Ellison (jordan.ellison@hotmail.com)
 * @brief the file that manages input and flow of the HexaPawn game. Creates
 * board and changes screens for each option.
 * @version 3.0
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 * 
 * @var the magic numbers to help flow of code: QUIT, PLAY, INFO, MENU, RULES
 */

#include "main.hpp"
using namespace std;

//constant game screen options
const int QUIT = 0;
const int PLAY = 1;
const int INFO = 2;
const int MENU = 3;
const int RULES = 4;

/**
 * @brief simple funciton make a string uppercase, because std::string doesnt 
 * have that. Takes the address of the actual string and goes index by index.
 * 
 * @param string the string to change
 */
void uppercase_helper(string& string){
    for(auto& ch : string)
        ch = toupper(ch);
}

/**
 * @brief option 1 or p. The function that manages the game itself. Creates the board and all
 * needed variables. Permanent while loop that takes the input move and 
 * manages flow of the game.
 * 
 * @retval int based on the flow, will return a different value once the game
 * ends. Defined as the variables above: QUIT, PLAY, INFO, MENU, or RULES.
 */
int play(){
    Board board;
    bool winner = false;
    string move = "D4D4";//starting with an illegal default move
    vector<string> past_moves;
    string e_warning = "none";//an exception that was given last round
    bool options = false;
    
    while(true){
        if(winner)//if win, print victory, else print next round
            board.print_victory(past_moves);
        else{
            //print game area
            cout<<"-------------------------------------------------------------------"<<endl;
            cout<<" Previous moves: ";
            for(auto& move : past_moves)
                if (&move == &(*past_moves.begin()))//only the first item
                    cout<<move;
                else cout << ", " << move;     //all other items   
            cout<<endl;

            if(e_warning != "none")
                cout << e_warning;
            else cout << endl;
            e_warning.assign("none");

            cout << board;

            //decision to print the options, if it was prompted
            if(options){
                options = false;//reset
                cout<<" Options: quit, play, info, menu, rules"<<endl;
            }else cout<<endl;

            cout << " Enter a move: ";
        }
        cin >> move;

        uppercase_helper(move);

        if(move == "OPTIONS" || move == "O")
            options = true;
        else if (move == "QUIT" || move == "Q")
            return QUIT;
        else if (move == "PLAY" || move == "P")
            return PLAY;
        else if(move == "RULES" || move == "R")
            return RULES;
        else if(move == "INFO" || move == "I")
            return INFO;
        else if(move == "MENU" || move == "M")
            return MENU;
        else if(move == "FORFEIT" || move == "F")
            winner = true;

        if(!options)//if they wanted to see the options, skip this game section
            try{
                winner = board.move(move);
                if (!winner) //only go to next round if there is still no winner
                    board.inc_round();
                past_moves.push_back(move);//only add the move if it was valid
            }catch(const exception& e){
                e_warning = " Excpetion: ";
                e_warning.append(e.what());
            }
    }
}

/**
 * @brief option 2 or i. Option screen for more inPerminantformation about the game. 
 * Prints words and waits for further options.
 * 
 * @retval int based on the input. Defined as the variables above: QUIT, PLAY,
 * INFO, MENU, or RULES.
 */
int info(){
    string input = "";

    while(true){
        cout<<" ------------------------------------------------------------------ "<<endl;
        cout<<"|                            GAME INFO                             |"<<endl;
        cout<<"| This game is based off of the paper \"Mathematical Games: How to  |"<<endl;
        cout<<"| Build a Game-Learning Machine and Then Teach It to Play and Win\" |"<<endl;
        cout<<"| by Martin Gardner. Currently, in my 3.0 version, there is no     |"<<endl;
        cout<<"| computer that learns how to beat you, I just wanted a complete   |"<<endl;
        cout<<"| deliverable. The computer that learns will come in v4.0. The     |"<<endl;
        cout<<"| learning computer works by iteratively removing all decisions    |"<<endl;
        cout<<"| that resulted in a loss, so its left with an exclusivly winning  |"<<endl;
        cout<<"| moveset, but the desing stage is a bit confusing for a program   |"<<endl;
        cout<<"| that plays the game that it is part of.                          |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"| Options: quit, play, info, menu, rules                           |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"  Select an option: ";
        cin>>input;
        uppercase_helper(input);

        if(input == "QUIT" || input == "Q")
            return QUIT;
        else if(input == "PLAY" || input == "P")
            return PLAY;
        else if(input == "MENU" || input == "M")
            return MENU;
        else if(input == "RULES" || input == "R")
            return RULES;
    }
}

/**
 * @brief option 3 or m. Option screen for the menu for the game. Prints the
 * words and waits for further option. 
 * 
 * @retval int based on the input. Defined as the variables above: QUIT, PLAY,
 * INFO, MENU, or RULES.
 */
int menu(){
    string input = "";
    
    while(true){
        cout<<" ------------------------------------------------------------------ "<<endl;
        cout<<"|                     Welcome to HexaPawn 3.0!                     |"<<endl;
        cout<<"| For the best experience, please resize your window so the lines  |"<<endl;
        cout<<"| are visible at each border; top, left side, and right side.      |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"| At any time, you can use any of these options, but any active    |"<<endl;
        cout<<"| game will be lost. Type \"options\" or \'o\' to see them again.      |"<<endl;
        cout<<"| Options:                                                         |"<<endl;
        cout<<"|        To return to this menu:         \"menu\" or \'m\'             |"<<endl;
        cout<<"|        To read the rules:              \"rules\" or \'r\'            |"<<endl;
        cout<<"|        To read more info on the game:  \"info\" or \'i\'             |"<<endl;
        cout<<"|        To play:                        \"play\" or \'p\'             |"<<endl;
        cout<<"|        To quit:                        \"quit\" or \'q\'             |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"  Thanks for playing, have fun! Enter an option: ";
        cin>>input;
        uppercase_helper(input);

        if(input == "QUIT" || input == "Q")
            return QUIT;
        else if(input == "PLAY" || input == "P")
            return PLAY;
        else if(input == "INFO" || input == "I")
            return INFO;
        else if(input == "RULES" || input == "R")
            return RULES;
    }
}

/**
 * @brief option 4 or r. Option screen for the rules for the game. Prints the
 * words and waits for further option. 
 * 
 * @retval int based on the input. Defined as the variables above: QUIT, PLAY,
 * INFO, MENU, or RULES.
 */
int rules(){//option 4 or r
    string input = "";

    while(true){
        cout<<" ------------------------------------------------------------------ "<<endl;
        cout<<"|                              RULES                               |"<<endl;
        cout<<"| The rules are simple, X goes first and each piece can only move  |"<<endl;
        cout<<"| like a chess pawn, so pieces can only move foreward if the space |"<<endl;
        cout<<"| ahead is clear or diagonally if the space is occupied by the     |"<<endl;
        cout<<"| opponant.                                                        |"<<endl;
        cout<<"| A player can win by a) getting to the end, b) taking all of the  |"<<endl;
        cout<<"| their opponant's pieces, or c) forcing their opponant into a     |"<<endl;
        cout<<"| stalemate (they cannot move).                                    |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"| Options: quit, play, info, menu, rules                           |"<<endl;
        cout<<"|                                                                  |"<<endl;
        cout<<"  Select an option: ";
        cin>>input;
        uppercase_helper(input);

        if(input == "QUIT" || input == "Q")
            return QUIT;
        else if(input == "PLAY" || input == "P")
            return PLAY;
        else if(input == "INFO" || input == "I")
            return INFO;
        else if(input == "MENU" || input == "M")
            return MENU;
    }
}

/**
 * @brief final screen for the game, once user has decided to exit.
 * 
 */
void goodbye(){
    cout<<"-------------------------------------------------------------------"<<endl;
    cout<<"\n Thanks for playing HexaPawn3.0!"<<endl;
    cout<<" I hope you will enjoy further updates in v4.0, hopefully with an"<<endl;
    cout<<" actual computer to play against, one that learns."<<endl;
    cout<<"\t-JE\n"<<endl;
    cout<<"Now cleaning up the directory..."<<endl;
}

/**
 * @brief the main function that organizes each screen requested by the user.
 * Starts on the menu screen. Each function returns the users next requested 
 * screen so the main function can send program to that option.
 * 
 * @retval int completion of the program, exit 0 for no errors.
 */
int main() {
    //0:quit, 1:play, 2:info, 3:menu, 4:rules
    int choice = 3;

    while(choice != 0){//run until quit, forfeit, or victory
        if(choice == 1)
            choice = play();
        else if(choice == 2)
            choice = info();
        else if(choice == 3)
            choice = menu();
        else if(choice == 4)
            choice = rules();           
    }

    goodbye();
    return 0;
}

/**
 * @brief This is the game board layout for v3.0. The game is fit for a 16 line
 * high by 70 character long screen, user is requested to resize their screen
 * to fit optimally.
 * 
 * ---------------------------------------------------------------------
 * | Previous moves: *space for previous moves*
 * | Exception: *various error printing*
 * |            *various error printing continues if needed*
 * | Round: *round*
 * |               1   2   3
 * |              -----------
 * |         A   |   |   |   |
 * |             |-----------|
 * |         B   |   |   |   |
 * |             |-----------|
 * |         C   |   |   |   |
 * |              -----------
 * |
 * | Options: quit, play, info, menu, rules *will print when promted with 'o' or "options"*
 *  Enter a move: *move entered*
 */
//test