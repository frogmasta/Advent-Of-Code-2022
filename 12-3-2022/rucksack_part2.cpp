/**
 * @file rucksack.cpp
 * @author Eric Roth
 * @brief 
 * @version 0.1
 * @date 2022-12-03
 * 
 * @copyright Copyright (c) 2022
 * 
 * Thought about using a disjoint sets data structure, but a map works just fine as well. 
 */

#include <iostream>

#include <cctype>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

/**
 * @brief Returns the character in common from all the input files. Works for part1 and part2. Can generalize to any input up to size 8 (uint8_t only has 8 bits).
 * 
 * @param inputs input strings
 * @return char common character (guaranteed only 1 from problem statement)
 */
char commonCharacter(const vector<string>& inputs) {
    unordered_map<char, uint8_t> char_count; // uint8_t hold the bit flags for its corresponding character

    for (uint8_t i = 0; i < inputs.size(); ++i) {
        for (const char& c : inputs[i]) {
            if (char_count.find(c) == char_count.end()) char_count.insert({c, 0});

            uint8_t& flags = char_count.at(c);
            flags = flags | (uint8_t) pow(2, i); // Marks bits as flags.
        }
    }

    uint8_t all_flags = pow(2, inputs.size()) - 1;
    for (const pair<char, uint8_t>& p : char_count) {
        if (p.second == all_flags) return p.first; // (e.x. input.size() is 3. 7 = 2^3 - 1 = 00000111, which is three flags in binary.
    }

    return '0'; // Something horribly wrong has occured.
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

    string line;
    vector<string> group;
    unsigned total_pts = 0;
    while(getline(infile, line)) {
        group.push_back(line);
        
        if (group.size() != 3) continue; 

        char common_letter = commonCharacter(group);

        // Converts character to "priority" value 
        if (isupper(common_letter)) total_pts += 27 + common_letter - 'A';
        else total_pts += 1 + common_letter - 'a';
        
        group.clear();
    }

    cout << "Total priorities is: " << total_pts << endl;
    return 0;
}