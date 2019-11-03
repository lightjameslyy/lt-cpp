#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/parentheses/32.longest-valid-parentheses.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> input = {
            "",
            "(()",
            ")()())"
    };
    for (int i = 0; i < input.size(); ++i)
        cout << s.longestValidParentheses(input[i]) << endl;
    return 0;
}
