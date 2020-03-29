#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

//#include "greedy/452.minimum-number-of-arrows-to-burst-balloons.cpp"
#include "string/KMP.cpp"

using namespace std;

int main() {
//    Solution sol;
    string pat = "aaab";
    vector<string> txt = {"aaaaaab", "aaac", "aaacaabaaabaaab"};
    KMP kmp(pat);
    for (int i = 0; i < txt.size(); ++i) {
        cout << kmp.search(txt[i]) << endl;
        cout << endl;
    }
    return 0;
}

