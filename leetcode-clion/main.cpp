#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/66.plus-one.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<vector<int>> digits = {
            {1, 2, 3},
            {4, 3, 2, 1},
            {9, 9, 9}
    };
    for (int i = 0; i < digits.size(); ++i) {
        print(sol.plusOne(digits[i]));
        cout << endl;
    }

    return 0;
}
