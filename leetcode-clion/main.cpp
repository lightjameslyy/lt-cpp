#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/substring/76.minimum-window-substring.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "ADOBECODEBANC",
            "ADOBECODEBANC",
            "ADOBECODEBANC"
    };
    vector<string> st = {
            "ABC",
            "AB",
            "ABN"
    };
    for (int i = 0; i < ss.size(); ++i) {
        cout << quotedString(s.minWindow(ss[i], st[i])) << endl;
    }
    return 0;
}
