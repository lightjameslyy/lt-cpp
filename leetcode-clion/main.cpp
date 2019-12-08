#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/sum/16.3sum-closest.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<vector<int>> vnums = {
            {-1, 2, 1, -4},
            {1,  1, 1, 1}
    };
    vector<int> target = {
            1,
            -100
    };
    for (int i = 0; i < target.size(); ++i) {
        cout << sol.threeSumClosest(vnums[i], target[i]) << endl;
    }
    return 0;
}

