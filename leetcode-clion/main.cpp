#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/parentheses/301.remove-invalid-parentheses.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> input = {
            "",
            "()())()",
            "(a)())()",
            ")(",
            ")(f",
            ")()("
    };
    for (int i = 0; i < input.size(); ++i) {
        print(s.removeInvalidParentheses(input[i]));
        cout << endl;
    }

    return 0;
}
