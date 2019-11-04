#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/subsequence/392.is-subsequence.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<string> s = {
            "",
            "abc",
            "axc",
            "b"
    };
    vector<string> t = {
            "",
            "ahbgdc",
            "ahbgdc",
            "c"
    };
    for (int i = 0; i < s.size(); ++i) {
        cout << sol.isSubsequence(s[i], t[i]) << endl;
    }

    return 0;
}
