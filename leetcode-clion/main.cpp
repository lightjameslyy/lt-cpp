#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/palindrome/131.palindrome-partitioning.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> ss = {
            "aab",
            "aababac",
            ""
    };
    for (int i = 0; i < ss.size(); ++i) {
        for (auto &ps : s.partition(ss[i])) {
            print(ps);
            cout << endl;
        }
    }
    return 0;
}
