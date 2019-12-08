#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/sum/18.4sum.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<vector<int>> vnums = {
            {1,  0,  -1, 0,  -2, 2},
            {-1, -5, -5, -3, 2,  5, 0, 4}
    };
    vector<int> target = {
            0,
            -7
    };
    for (int i = 0; i < target.size(); ++i) {
        for (auto res : sol.fourSum(vnums[i], target[i])) {
            print(res);
            cout << " ";
        }
        cout << endl;
    }
    return 0;
}

