#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/palindrome/266.palindrome-permutation.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "code",
            "aab",
            "carerac"
    };
    for (int i = 0; i < ss.size(); ++i) {
        cout << s.canPermutePalindrome(ss[i]) << endl;
    }
    return 0;
}
