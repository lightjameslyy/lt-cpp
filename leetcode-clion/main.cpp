#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/7.reverse-integer.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<int> vals = {
            123,
            -123,
            120
    };
    for (int i = 0; i < vals.size(); ++i) {
        cout << sol.reverse(vals[i]) << endl;
    }

    return 0;
}
