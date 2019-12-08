#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/sum/259.3sum-smaller.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<vector<int>> vnums = {
            {-2, 0, 1, 3}
    };
    vector<int> target = {
            2
    };
    for (int i = 0; i < target.size(); ++i) {
        cout << sol.threeSumSmaller(vnums[i], target[i]) << endl;
    }
    return 0;
}

