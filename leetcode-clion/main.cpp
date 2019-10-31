#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/substring/159.longest-substring-with-at-most-two-distinct-characters.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "eceba",
            "ccaabbb"
    };
    for (int i = 0; i < ss.size(); ++i) {
        cout << s.lengthOfLongestSubstringTwoDistinct(ss[i]) << endl;
    }
    return 0;
}
