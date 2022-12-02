/**
 * @file calories.cpp
 * @author Eric Roth
 * @brief 
 * @version 0.1
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

#include "../lib/heap.h"

using namespace std;

/**
 * @brief Checks whether the first number is bigger than the second. 
 * 
 * @param first first number
 * @param second second number
 * @return true first is bigger
 * @return false second is bigger 
 */
bool maxHeap(unsigned first, unsigned second) {
    return first > second;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "No input file and/or no number of max elves specified" << endl;
        return 1;
    }

    string fname = argv[1];
    ifstream file(fname);

    if (!file.is_open()) {
        cout << "Issue opening input file: " << fname << endl;
        return 1;
    }

    string line;
    unsigned current_cals = 0;
    Heap<unsigned> h(&maxHeap);
    while(getline(file, line)) {
        try {
            unsigned item_cal = stoi(line);
            current_cals += item_cal;
        } catch (const invalid_argument& ia) {
            h.insert(current_cals);
            current_cals = 0;
        }
    }

    unsigned max_elves = stoi(argv[2]);
    vector<unsigned> elf_calories;
    for (unsigned i = 0; i < max_elves; ++i) {
        elf_calories.push_back(h.remove());
    }

    unsigned total_calories = accumulate(elf_calories.begin(), elf_calories.end(), 0);
    cout << "The amount of total calories carried by the " << max_elves << " elves with maximum calories is: " << total_calories << endl;
    return 0;
}