#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/substring/30.substring-with-concatenation-of-all-words.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "barfoothefoobarman",
            "wordgoodgoodgoodbestword",
            "a"
    };
    vector<vector<string>> words = {
            {"foo", "bar"},
            {"word", "good", "best", "word"},
            {"a", "a"}
    };
    for (int i = 0; i < ss.size(); ++i) {
        print(s.findSubstring(ss[i], words[i]));
    }
    return 0;
}
