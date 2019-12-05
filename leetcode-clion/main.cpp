#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/69.sqrtx.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<int> x = {
            1,
            4,
            8,
            9,
            12,
            100
    };
    for (int i = 0; i < x.size(); ++i) {
        cout << sol.mySqrt(x[i]) << endl;
    }

    return 0;
}

