#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "dynamic_programming/2d/72.edit-distance.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<string> word1 = {
        "horse",
        "intention"
    };
    vector<string> word2 = {
        "ros",
        "execution"
    };
    for (int i = 0; i < word1.size(); ++i) {
        cout << sol.minDistance(word1[i],word2[i]);
        cout << endl;
    }
    return 0;
}

