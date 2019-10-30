#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/substring/395.longest-substring-with-at-least-k-repeating-characters.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "aaabb",
            "ababbc",
            "aaddddfdgggaawrawwradsfgabb"
    };
    vector<int> ks = {
            3,
            2,
            3
    };
    for (int i = 0; i < ss.size(); ++i) {
        cout << s.longestSubstring(ss[i], ks[i]) << endl;
    }
    return 0;
}
