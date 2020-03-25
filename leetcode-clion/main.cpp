#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "greedy/452.minimum-number-of-arrows-to-burst-balloons.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<vector<vector<int>>> intervals = {
            {{10,16}, {2,8}, {1,6}, {7,12}}
    };
    for (int i = 0; i < intervals.size(); ++i) {
        cout << sol.findMinArrowShots(intervals[i]) << endl;
        cout << endl;
    }
    return 0;
}

