/**
 * @file tuning_part1.cpp
 * @author Eric Roth
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

/**
 * @brief Helper function to determine if the input string meets the specification given.
 * 
 * @param input vector of character counts
 * @return true if it's a valid "start-of-message" marker
 * @return false otherwise
 */
bool checkValid(const vector<size_t>& char_count) {
    bool valid = true;
    for (const size_t& size : char_count) {
        if (size > 1) valid = false;
    }
    return valid;
}

/**
 * @brief Finds the first "start-of-message" marker and returns the number of characters processed.
 * 
 * @param signal input signal
 * @return size_t number of characters processed
 */
size_t findMarker(const string& signal) {
    size_t num_processed = 14;
    string currently_processing = signal.substr(0, 14);

    vector<size_t> char_count(26, 0); // 'a' is index 0, 'b' is index 1, etc. 
    for (const char& c : currently_processing) {
        size_t idx = c - 'a';
        char_count[idx] += 1;
    }

    if (checkValid(char_count)) return num_processed;

    while(num_processed < signal.size()) {
        num_processed++;
        char next_char = signal[num_processed - 1];

        size_t next_char_idx = next_char - 'a';
        size_t removed_char_idx = currently_processing[0] - 'a';
        char_count[next_char_idx] += 1;
        char_count[removed_char_idx] -= 1;

        currently_processing += next_char;
        currently_processing.erase(currently_processing.begin());

        if (checkValid(char_count)) return num_processed;
    }

    return num_processed; // Did not find a valid marker
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
    getline(infile, line);

    size_t marker = findMarker(line);

    cout << "The number of characters we need to process until we reach a valid marker is: " << marker << endl;
    return 0;
}