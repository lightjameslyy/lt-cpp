#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "dynamic_programming/887.super-egg-drop.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<int> K = {
        1,
        2,
        3
    };
    vector<int> N = {
        2,
        6,
        14
    };
    for (int i = 0; i < K.size(); ++i) {
        cout << sol.superEggDrop(K[i], N[i]) << endl;
        cout << endl;
    }
    return 0;
}

