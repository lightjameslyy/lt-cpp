#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/367.valid-perfect-square.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<int> n = {
            1,
            16,
            14
    };
    for (int i = 0; i < n.size(); ++i) {
        cout << sol.isPerfectSquare(n[i]) << endl;
    }

    return 0;
}

