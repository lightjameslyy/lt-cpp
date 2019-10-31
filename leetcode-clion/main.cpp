#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/substring/340.longest-substring-with-at-most-k-distinct-characters.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "eceba",
            "aa",
            "ece ert 54q3 456 q34ba"
    };
    vector<int> ks = {
            2,
            1,
            4
    };
    for (int i = 0; i < ss.size(); ++i) {
        cout << s.lengthOfLongestSubstringKDistinct(ss[i], ks[i]) << endl;
    }
    return 0;
}
