#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/365.water-and-jug-problem.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<int> x = {3, 2};
    vector<int> y = {5, 6};
    vector<int> z = {4, 5};
    for (int i = 0; i < x.size(); ++i) {
        cout << sol.canMeasureWater(x[i], y[i], z[i]) << endl;
    }

    return 0;
}

