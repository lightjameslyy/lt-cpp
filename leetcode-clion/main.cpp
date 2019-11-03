#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/parentheses/22.generate-parentheses.cpp"

using namespace std;

int main() {
    Solution s;
    print(s.generateParenthesis(3));
    cout << endl;
    print(s.generateParenthesis(0));
    cout << endl;
    return 0;
}
