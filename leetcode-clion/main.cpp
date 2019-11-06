#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/8.string-to-integer-atoi.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<string> s = {
            "42",
            "    -42",
            "4193 aejofi josdf",
            "uhajf iasj 987",
            "-9283758234765234",
            "2147483646"
    };
    for (int i = 0; i < s.size(); ++i) {
        cout << sol.myAtoi(s[i]) << endl;
    }

    return 0;
}
