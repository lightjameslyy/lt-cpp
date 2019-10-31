#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/palindrome/125.valid-palindrome.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "A man, a plan, a canal: Panama",
            "race a car"
    };
    for (int i = 0; i < ss.size(); ++i) {
        cout << s.isPalindrome(ss[i]) << endl;
    }
    return 0;
}
