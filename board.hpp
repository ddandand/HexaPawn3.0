/**
 * @file board.hpp
 * @author Jordan Ellison (jordan.ellison@hotmail.com)
 * @brief header class for the board object. This houses all of the methods 
 * that can be used either internally or externally as an interface with the
 * main() flow of the code. This is the list of every function of the Board 
 * object class; format and legality validation, move performance, state check,
 * state changing, constructing, and other trivial tasks.
 * @see board.cpp for detailed descriptions of this small class.
 * @version 3.0
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Board{
private:
    vector<vector<char>> setup;
    int round;
    int x_pieces;
    int o_pieces;

    void perform_move(vector<int> move);
    bool check_win();
    vector<int> reformat_move(string& move);
    void validate_format(vector<int> move);
    void o_legal(vector<int> move, vector<vector<char>> setup);
    void x_legal(vector<int> move, vector<vector<char>> setup);
    void validate_legality(vector<int> move, vector<vector<char>> setup, int current_round);


public:
    Board();
    void inc_round();
    bool move(string& move);
    void print_victory(vector<string> move_list);
    friend ostream& operator<<(ostream& stream, const Board& self);

};
//test