#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "greedy/435.non-overlapping-intervals.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<vector<vector<int>>> intervals = {
            {{1,2}, {1,2}, {1,2}},
            {{1,2}, {2,3}}
    };
    for (int i = 0; i < intervals.size(); ++i) {
        cout << sol.eraseOverlapIntervals(intervals[i]) << endl;
        cout << endl;
    }
    return 0;
}

