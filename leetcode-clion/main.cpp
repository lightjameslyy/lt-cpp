#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/palindrome/5.longest-palindromic-substring.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "babad",
            "cbbd"
    };
    for (int i = 0; i < ss.size(); ++i) {
        cout << s.longestPalindrome(ss[i]) << endl;
    }
    return 0;
}
