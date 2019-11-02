#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/palindrome/267.palindrome-permutation-ii.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "",
            "abc",
            "aabb",
            "abacaabcc"
    };
    for (int i = 0; i < ss.size(); ++i) {
        //s.generatePalindromes(ss[i]);
        print(s.generatePalindromes(ss[i]));
        cout << endl;
    }
    return 0;
}
