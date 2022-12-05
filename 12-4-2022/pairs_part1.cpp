/**
 * @file pairs_part1.cpp
 * @author Eric Roth
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 */
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/**
 * @brief Determines if two intervals fully overlap.
 * 
 * @param p1 first interval
 * @param p2 second interval
 * @return true there is total overlap
 * @return false there is not total overlap
 */
bool total_overlap(pair<int, int> p1, pair<int, int> p2) {
    return (p1.first >= p2.first && p1.second <= p2.second) || (p1.first <= p2.first && p1.second >= p2.second);
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
    unsigned total_overlaps = 0;
    while(getline(infile, line)) {
        vector<string> nums;
        string current_num = "";
        for (const char& c : line) {
            if (c - '0' < 0 || c - '0' > 9) {
                nums.push_back(current_num);
                current_num = "";
            }
            else current_num += c;
        }
        nums.push_back(current_num);

        vector<int> nums_i;
        for (const string& s : nums) {
            nums_i.push_back(stoi(s));
        }

        if (total_overlap(pair<int, int>(nums_i[0], nums_i[1]), pair<int, int>(nums_i[2], nums_i[3]))) {
            total_overlaps += 1;
        }
    }

    cout << "Total overlaps is: " << total_overlaps << endl;
    return 0;
}