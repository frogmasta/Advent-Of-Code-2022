/**
 * @file rps_part2.cpp
 * @author Eric Roth
 * @brief 
 * @version 0.1
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * @brief Returns the number of points the player gets this game. 0 for lose, 3 for draw, 6 for win. Plus the points of throwing that hand.
 * 
 * @param p_move Player Move (0 is Rock, 1 is Paper, 2 is Scissors)
 * @param e_move Elf Move (0 is Rock, 1 is Paper, 2 is Scissors)
 * @return unsigned resulting score for the player
 */
unsigned points(unsigned p_move, unsigned e_move) {
    unsigned shape_score = (p_move + 1);

    if (p_move == e_move) return 3 + shape_score; // tie
    else if ((p_move + 1) % 3 == e_move) return 0 + shape_score; // win
    else return 6 + shape_score; // lose
}

/**
 * @brief Given the elf's move and the desired result, pick the right move to make.
 * 
 * @param e_move elf's move (0 is Rock, 1 is Paper, 2 is Scissors)
 * @param outcome outcome predicted (X is lose, Y is draw, Z is win)
 * @return unsigned move to choose (0 is Rock, 1 is Paper, 2 is Scissors)
 */
unsigned chooseMove(unsigned e_move, string outcome) {
    if (outcome == "X") return (e_move + 2) % 3; // lose
    else if (outcome == "Y") return e_move; // tie
    else return (e_move + 1) % 3; // win
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "No input file specified." << endl;
        return 1;
    }

    string fname = argv[1];
    ifstream infile(fname);

    if (!infile.is_open()) {
        cout << "There was an error opening the specified file." << endl;
        return 1;
    }

    unsigned total_score = 0;
    string line;
    while(getline(infile, line)) {
        istringstream iss(line);
        string elf_move, outcome;
        iss >> elf_move;
        iss >> outcome;
        unsigned e_move, p_move;
        e_move = elf_move[0] - 'A';
        p_move = chooseMove(e_move, outcome);
        total_score += points(p_move, e_move);
    }
    
    cout << "Total points for all the games is: " << total_score;
    return 0;
}