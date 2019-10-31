#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/palindrome/9.palindrome-number.cpp"

using namespace std;

int main() {
    Solution s;
    vector<int> x = {
            121,
            -121,
            10
    };
    for (int i = 0; i < x.size(); ++i) {
        cout << s.isPalindrome(x[i]) << endl;
    }
    return 0;
}
