#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/subsequence/115.distinct-subsequences.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<string> s = {
            "",
            "rabbbit",
            "babgbag"
    };
    vector<string> t = {
            "",
            "rabbit",
            "bag"
    };
    for (int i = 0; i < s.size(); ++i) {
        cout << sol.numDistinct(s[i], t[i]) << endl;
    }

    return 0;
}
