#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/substring/3.longest-substring-without-repeating-characters.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> input = {
            "abcabcbb",
            "bbbbb",
            "pwwkew",
            "abcakjlakLKHIbc2345bb"
    };
    for (int i = 0; i < input.size(); ++i) {
        cout << s.lengthOfLongestSubstring(input[i]) << endl;
    }
    return 0;
}
