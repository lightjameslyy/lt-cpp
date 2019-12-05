#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/29.divide-two-integers.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<int> dividend = {
            1 << 31,
            -2147483648,
            10,
            7
    };
    vector<int> divisor = {
            -1,
            1,
            3,
            -3
    };
    for (int i = 0; i < dividend.size(); ++i) {
        cout << sol.divide(dividend[i], divisor[i]) << endl;
    }

    return 0;
}

