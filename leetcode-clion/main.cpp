#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/50.powx-n.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<double> x = {
            2.0,
            2.1,
            2.0
    };
    vector<int> n = {
            10,
            3,
            -2
    };
    for (int i = 0; i < x.size(); ++i) {
        cout << sol.myPow(x[i], n[i]) << endl;
    }

    return 0;
}

