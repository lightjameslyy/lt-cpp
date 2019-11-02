#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/parentheses/20.valid-parentheses.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "",
            "()",
            "()[]{}",
            "(]",
            "([)]",
            "{[]}",
            "[",
            "]"
    };
    for (int i = 0; i < ss.size(); ++i) {
        cout << s.isValid(ss[i]) << endl;
    }
    return 0;
}
