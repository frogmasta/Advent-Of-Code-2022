/**
 * @file crates_part2.cpp
 * @author Eric Roth
 * @brief 
 * @version 0.1
 * @date 2022-12-05
 * 
 * @copyright Copyright (c) 2022
 */
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/**
 * @brief Moves crates based on input specifications. For part 2, they all move together!
 * 
 * @param stacks all the crates stacks
 * @param num number of crates to move
 * @param source where the crates are coming from
 * @param dest where the crates are going to
 */
void move_crates(vector<stack<char>>& stacks, size_t num, size_t source, size_t dest) {
    stack<char> to_move;
    for (size_t i = 0; i < num; ++i) {
        to_move.push(stacks[source].top());
        stacks[source].pop();  
    }

    while(!to_move.empty()) {
        stacks[dest].push(to_move.top());
        to_move.pop();
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Didn't provide an input file." << endl;
        return 1;
    }

    string fname = "data/";
    fname += argv[1];
    ifstream infile(fname);

    if (!infile.is_open()) {
        cout << "Issue opening the file. " << endl;
        return 1;
    }

    vector<string> lines;
    string line;
    size_t seperator_line, current_line = 0;
    while(getline(infile, line)) {
        lines.push_back(line);
        if (line == "") seperator_line = current_line;
        current_line++;
    }

    // Populate the crate stacks
    vector<stack<char>> stacks;
    string stacks_line = lines[seperator_line - 1];
    istringstream iss(stacks_line);
    string current_stack;
    while(iss >> current_stack) {
        stacks.push_back(stack<char>());
        size_t idx = stacks_line.find_first_of(current_stack); // index of column these crates are in

        // Line below seperator is crate numbers, line below that is the actual crates.
        for (int i = seperator_line - 2; i >= 0; --i) {
            char current_crate = lines[i][idx];
            if (current_crate == ' ') break;

            stacks.back().push(current_crate);
        }
    }

    // Start parsing moves. seperator_line + 1 is the start of such rows in the input.
    for (size_t i = seperator_line + 1; i < lines.size(); ++i) {
        line = lines[i];
        iss.clear(); // DON'T remove this line!
        iss.str(line);
        vector<string> line_words;
        string word;
        while(iss >> word) {
            line_words.push_back(word);
        }

        size_t num = stoi(line_words[1]);
        size_t source = stoi(line_words[3]) - 1; // Offset for indexing in vector
        size_t dest = stoi(line_words[5]) - 1; // Offset for indexing in vector

        move_crates(stacks, num, source, dest);
    }

    string out = "";
    for (const stack<char>& s : stacks) {
        out += s.top();
    }

    cout << "The crates on the top of each stack are: " << out << endl;
    return 0;
}