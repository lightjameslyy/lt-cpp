#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/67.add-binary.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<string> a = {
            "11",
            "1010"
    };
    vector<string> b = {
            "1",
            "1011"
    };
    for (int i = 0; i < a.size(); ++i) {
        cout << sol.addBinary(a[i], b[i]) << endl;
    }

    return 0;
}
