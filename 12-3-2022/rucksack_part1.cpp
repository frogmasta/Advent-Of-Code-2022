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
#include <string>
#include <sstream>
#include <unordered_set>

using namespace std;

/**
 * @brief Returns the character in common from the first and second word. Completed for part 1.
 * 
 * @param first first word
 * @param second second word
 * @return char common character (assuming they have one)
 */
char commonCharacter(const string& first, const string& second) {
    unordered_set<char> first_half;

    for (const char& c : first) {
        first_half.insert(c);
    }

    for (const char& c : second) {
        if (first_half.find(c) != first_half.end()) return c;
    }

    return '0'; // Something has gone horribly wrong
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
    unsigned total_pts = 0;
    while(getline(infile, line)) {
        string left_rucksack = line.substr(0, line.size() / 2);
        string right_rucksack = line.substr(line.size() / 2);

        char common_letter = commonCharacter(left_rucksack, right_rucksack);

        // Converts character to "priority" value 
        if (isupper(common_letter)) total_pts += 27 + common_letter - 'A';
        else total_pts += 1 + common_letter - 'a';
    }

    cout << "Total priorities is: " << total_pts << endl;
    return 0;
}