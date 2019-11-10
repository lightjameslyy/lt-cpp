#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/43.multiply-strings.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<string> a = {
            "2",
            "123"
    };
    vector<string> b = {
            "3",
            "456"
    };
    for (int i = 0; i < a.size(); ++i) {
        cout << sol.multiply(a[i], b[i]) << endl;
    }

    return 0;
}
