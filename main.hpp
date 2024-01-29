/**
 * @file main.hpp
 * @author Jordan Ellison (jordan.ellison@hotmail.com)
 * @brief This file is unecessary, it is mainly just for my own vision. So I
 * could see all of the functions within the main.cpp file. Houses all of
 * the function signatures from main.cpp; upper_helper() raises the case of a
 * whole string, play(/info(/menu(/rules(/goodbye() are the different screen
 * printing options, main() is program flow controller.
 * 
 * @version 3.0
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 */
#include "board.hpp"

void uppercase_helper(string& string);

int play();
int info();
int menu();
int rules();
void goodbye();

int main();