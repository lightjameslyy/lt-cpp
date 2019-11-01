#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/palindrome/336.palindrome-pairs.cpp"

using namespace std;

int main() {
    Solution s;
    vector<vector<string>> ss = {
            {"abcd", "dcba", "lls", "s", "sssll"},
            {"bat",  "tab",  "cat"},
            {"a",    "abc",  "aba", ""}
    };
    for (int i = 0; i < ss.size(); ++i) {
        //cout << s.palindromePairs(ss[i]) << endl;
        for (auto &vec : s.palindromePairs(ss[i])) {
            print(vec);
            cout << ", ";
        }
        cout << endl;
    }
    return 0;
}
