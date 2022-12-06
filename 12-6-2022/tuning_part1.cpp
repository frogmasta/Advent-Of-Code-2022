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
#include <vector>

using namespace std;

/**
 * @brief Helper function to determine if the input string meets the specification given.
 * 
 * @param input 4-digit input signal
 * @return true if it's a "start-of-packet" marker
 * @return false otherwise
 */
bool checkValid(const string& input) {
    bool valid = true;
    for (size_t i = 0; i < input.size(); ++i) {
        for (size_t j = i + 1; j < input.size(); ++j) {
            if (input[i] == input[j]) valid = false;
        }
    }
    return valid;
}

/**
 * @brief Finds the first "start-of-packet" marker and returns the number of characters processed.
 * 
 * @param signal input signal
 * @return size_t number of characters processed
 */
size_t findMarker(const string& signal) {
    size_t num_processed = 4;
    string currently_processing = signal.substr(0, 4);
    if (checkValid(currently_processing)) return num_processed;

    while(num_processed < signal.size()) {
        num_processed++;

        currently_processing += signal[num_processed - 1];
        currently_processing.erase(currently_processing.begin());

        if (checkValid(currently_processing)) return num_processed;
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