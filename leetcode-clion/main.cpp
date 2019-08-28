#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/advanced/65.valid-number.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> strs = {
            "0",
            " 0.1 ",
            "abc",
            "1 a",
            "2e10",
            " -90e3   ",
            " 1e",
            "e3",
            " 6e-1",
            " 99e2.5    ",
            "53.5e93",
            " --6 ",
            "-+3",
            "95a54e53",
            ""
    };
    for (const string &str : strs) {
        cout << quotedString(trim(str)) << endl;
        cout << quotedString(str) << ": " << (s.isNumber(str) ? "true" : "false") << endl;
    }
    return 0;
}
