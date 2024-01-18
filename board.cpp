/**
 * @brief Board class housing all of the necessary funcionality and data for
 * the board object. 
 * 
 * @throws runtime_error based on the user's input. This serves to check the
 * format and legality of a move, to catch any errors. In other words, to help
 * parse the input. The error will stop all flow back to the play() function
 * in the case that there is something illegal or unformatted, then will 
 * re-prompt the user after displaying the error. Honestly, I dont know if I 
 * could have chosen a better exception to throw, it just came from inexperience
 * and looking for the best option to make it work and look clean.
 * 
 */
#include "board.hpp"
using namespace std;

/**
 * @brief Construct a new Board:: Board object. Set the board.setup to a 
 * fresh clean board before the game. set the round and piece numbers to
 * thier required starting values. 
 */
Board::Board(){
    setup.assign({
        {'O', 'O', 'O'}, 
        {' ', ' ', ' '}, 
        {'X', 'X', 'X'}});

    round = 1;
    x_pieces = 3;
    o_pieces = 3;
};

/**
 * @brief the incrementor for the board.round variable. Used to maintain the
 * decoupling of data and logic.
 * 
 */
void Board::inc_round(){
    this->round++;
}

/**
 * @brief this function will apply the changes to the board configuration (if
 * the flow of the program deemed the move valid and legal). Place piece in 
 * new position, make the previous position blank.
 * 
 * @param move the users confirmed move.
 */
void Board::perform_move(vector<int> move){
    setup[move[2]][move[3]] = setup[move[0]][move[1]];
    setup[move[0]][move[1]] = ' ';

}

/**
 * @brief checks if there are any victory states on the board. Victory is
 * checked as a piece in the opposing end-zone, a player having no more
 * pieces, or if a player was forced into a stalemate on their turn. 
 * Note: I know that this code is very ugly, I couldn't find an elegant 
 * solution to find a forced stalemate so I just made a brute force where it
 * checks the necessary surrounding squares for possible moves, it creates a 
 * move and checks the legality of it using the other defined Board functions.
 * 
 * @return true if there was a victory (the player who just went must have won) 
 * @return false if there is still no victory state.
 */
bool Board::check_win(){
    vector<int> move_test = {0,0,0,0};
    bool x_move = false;
    bool o_move = false;

    //all of the opponent's pieces are gone =  player won
    if ((x_pieces == 0) || (o_pieces == 0))
        return true;//somebody won

    ///player's piece in opponent's starting line = player won
    for (auto &ch : setup[0])
        if (ch == 'X')
            return true;//X won
    for (auto &ch : setup[2])
        if (ch == 'O')
            return true;//O won

    //opponent forced into stalemate = player won
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++)
            if (setup[i][j] == 'X'){

                if (setup[i-1][j] == ' ')//forwards 
                    x_move = true;
                
                try{
                    if (setup[i-1][j-1] == 'O')//left diagonal
                        x_move = true;
                }catch(const exception& e){
                    //test was out of bounds
                }

                try{
                    if (setup[i-1][j+1] == 'O')//right diagonal
                        x_move = true;
                }catch(const exception& e){
                    //test was out of bounds
                }             

            }else if (setup[i][j] == 'O'){

                if (setup[i+1][j] == ' ')//forwards 
                    o_move = true;
                
                try{
                    if (setup[i+1][j-1] == 'X')//left diagonal
                        o_move = true;
                }catch(const exception& e){
                    //test was out of bounds
                }

                try{
                    if (setup[i+1][j+1] == 'X')//right diagonal
                        o_move = true;
                }catch(const exception& e){
                    //test was out of bounds
                }                
            }
    }//end of stalemate for loop

    //if no opponant move was found, then they are in stalemate, so player won
    if (round%2 == 0)//O's turn
        return !x_move;
    else//X's turn
        return !o_move;
}

/**
 * @brief the engine called by the play() function. This function takes the user's
 * move and performs the board-side operations on it: takes move, reformats it, 
 * validates the format and legality, then performs the move, and lastly checks 
 * for a winning condition (all assuming there is nothing illegal or invalid).
 * 
 * @param move user's requested move.
 * @return true if there was a winning condigion.
 * @return false if there was no winning condition.
 */
bool Board::move(string& move){
    //if the format and legality completed without an exception, the move can confidently be performed
    vector<int> new_move = reformat_move(move);
    validate_format(new_move);   
    validate_legality(new_move, setup, round);
    Board::perform_move(new_move);

    return check_win();//if somebody won or not
}

/**
 * @brief once the play() function has found a victory condition, this will
 * print the winning board one more time and prepate to prompty the user for
 * a new command; one of QUIT, PLAY, INFO, MENU, or RULES.
 * 
 * @param move_list requires input of the moveset for this game.
 */
void Board::print_victory(vector<string> move_list){
    char winner;

    if(round%2 == 0)
        winner = 'O';
    else winner = 'X';

    cout<<"-------------------------------------------------------------------"<<endl;
    cout<<" Previous moves: ";
    for(auto& move : move_list)
        if (&move == &(*move_list.begin()))//only the first item
            cout<<move;
        else cout << ", " << move;     //all other items   
    
    cout<<endl<<endl;
    cout<<*this;
    cout<<" Options: quit, play (to play again), info, menu, rules"<<endl;
    cout<<" The winner is "<<winner<<"! Choose an option to continue: ";
}

/**
 * @brief takes a string version provided by the user and turns it into a 4
 * int vector to integrate with the board.setup cleanly.
 * 
 * @param move the original move provided by the user.
 * @return vector<int> new_move as the complete and set integer encoding for
 * the setup.
 * 
 * @throws runtime_error checks the length of the move.
 */
vector<int> reformat_move(string& move){
    if(move.length() != 4) 
        throw runtime_error("Invalid format. Must be 4 characters long. \n            Please enter in the format of \"A1B2\".");
    
    vector<int> new_move;
    //set all parts of new_move to integrate with the board[][]
    new_move.push_back(move[0] - 17 - '0');
    new_move.push_back(move[1] - 1 - '0');
    new_move.push_back(move[2] - 17 - '0');
    new_move.push_back(move[3] - 1 - '0');

    return new_move;
}

/**
 * @brief takes in the int vector move from the user (after reformatting it)
 * and parses the rest of the formatting; that all parts of the vector are 
 * within the bounds of the board (1, 2, or 3), the piece only moves forward
 * relative to its position, and that it is only moving at most one space 
 * forward and/or sideways.
 * 
 * @param move the move requested by the user.
 * @throws runtime_error if player input is invalid, not moving 1 space forward,
 * or if moving more than one space to the side.
 */
void validate_format(vector<int> move){
    //if any characters are out of the bounds of the board (1-3) return false
    for (auto &ch : move)
        if (ch < 0 || 2 < ch)
            throw runtime_error("Invalid format. Must only include A, B, C or 1, 2, 3. \n            Please enter in the format of \"A1B2\".");

    //make sure player is moving forwards one space
    int difference = abs(move[0] - move[2]);
    if (difference != 1)
        throw runtime_error("Invalid format. You can only move 1 space forwards at a time.");

    //make sure moving at most one space sideways
    difference = abs(move[1] - move[3]);
    if (difference > 1)
        throw runtime_error("Invalid format. You can only move 1 space to the side at a time.");
}

/**
 * @brief checks the legality for a move from the O-POV. The only options are
 * either the function will run and complete normally or it will throw an 
 * exception, if it finishes then the move was valid, otherwise it must be 
 * re-entered.
 * 
 * @param move user's move request.
 * @param setup the current board configuration.
 * 
 * @throws runtime_error if player tries to go relative backwards, tried to
 * move without being in the starting square, the space ahead isnt empty, or
 * tries diagonally but isnt actually taking an X space.
 */
void o_legal(vector<int> move, vector<vector<char>> setup){
    //if not moving forwards (decreasing ASCII) its illegal
    if(move[0] >= move[2])  
        throw runtime_error("Illegal move. You can only move forwards.");

    //must start on an X square
    if (setup[move[0]][move[1]] != 'O') 
        throw runtime_error("Illegal move. O must be in it's starting position.");

    if (move[1] == move[3]){//only moving forwards
      if (setup[move[2]][move[3]] != ' ')//space ahead must be clear
        throw runtime_error("Illegal move. If O is moving forwards, there must be an empty space ahead.");
        
    }else{//moving forwards and sideways (diagonally)
      if (setup[move[2]][move[3]] != 'X')//ending in opponants space
        throw runtime_error("Illegal move. If O is moving diagonally, they must be taking X's square.");
    }
}

/**
 * @brief checks the legality for a move from the X-POV. The only options are
 * either the function will run and complete normally or it will throw an 
 * exception, if it finishes then the move was valid, otherwise it must be 
 * re-entered.
 * 
 * @param move user's move request.
 * @param setup the current board configuration.
 * 
 * @throws runtime_error if player tries to go relative backwards, tried to
 * move without being in the starting square, the space ahead isnt empty, or
 * tries diagonally but isnt actually taking an O space.
 */
void x_legal(vector<int> move, vector<vector<char>> setup){
    //if not moving forwards (decreasing ASCII) its illegal
    if(move[0] <= move[2])  
        throw runtime_error("Illegal move. You can only move forwards.");

    //must start on an X square
    if (setup[move[0]][move[1]] != 'X') 
        throw runtime_error("Illegal move. X must be in it's starting position.");

    if (move[1] == move[3]){//only moving forwards
      if (setup[move[2]][move[3]] != ' ')//space ahead must be clear
        throw runtime_error("Illegal move. If X is moving forwards, there must be an empty space ahead.");
        
    }else{//moving forwards and sideways (diagonally)
      if (setup[move[2]][move[3]] != 'O')//ending in opponants space
        throw runtime_error("Illegal move. If X is moving diagonally, they must be taking O's square.");
    }
}

/**
 * @brief contains the logic the validating the legality of each move, calls
 * the required functions based on X and O. This function is kind of unnecessary
 * but it made the flow feel more decoupled and independant.
 * Note: by definition, if the format is valid, the move is within the bounds. 
 * Only A-C and 1-3 
 * 
 * @throws runtime_error will forward the exception if the move was illegal or 
 * unformatted, if necessary.
 *
*/
void validate_legality(vector<int> move, vector<vector<char>> setup, int current_round){
    if(current_round%2 == 0)
        o_legal(move, setup);//round is even
    else 
        x_legal(move, setup);//round is odd 
}

/**
 * @brief overridden function for printing the formatting of the board object.
 * 
 * @param stream the io stream to the screen.
 * @param self the board object to print.
 * @return ostream& the io stream to continue printing if necessary.
 */
ostream& operator<<(ostream& stream, const Board& self) {
stream << "\n Round: " << self.round << '\n';
stream << "\t      1   2   3\n\n";
stream << "\t     -----------\n";
stream << "\tA   | " << self.setup[0][0] << " | " << self.setup[0][1] << " | " << self.setup[0][2] << " |\n";
stream << "\t    |-----------|\n";
stream << "\tB   | " << self.setup[1][0] << " | " << self.setup[1][1] << " | " << self.setup[1][2] << " |\n";
stream << "\t    |-----------|\n";
stream << "\tC   | " << self.setup[2][0] << " | " << self.setup[2][1] << " | " << self.setup[2][2] << " |\n";
stream << "\t     -----------\n";

return stream;
};
//test