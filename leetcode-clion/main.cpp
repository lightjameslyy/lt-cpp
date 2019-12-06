#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/sum/15.3sum.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<vector<int>> vnums = {
            {-1, 0,  1,  2, -1, -4},
            {0,  0,  0},
            {-2, -2, -2, 0, 0,  0, 1, 1, 1, 1, 1, 2}
    };
    for (auto nums : vnums) {
        for (auto res : sol.threeSum(nums)) {
            print(res);
            cout << " ";
        }
        cout << endl;
    }
    return 0;
}

