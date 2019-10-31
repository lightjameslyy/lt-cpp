#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/palindrome/214.shortest-palindrome.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "aacecaaa",
            "abcd"
    };
    for (int i = 0; i < ss.size(); ++i) {
        cout << s.shortestPalindrome(ss[i]) << endl;
    }
    return 0;
}
