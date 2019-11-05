#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/subsequence/187.repeated-dna-sequences.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<string> s = {
            "",
            "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
    };
    for (int i = 0; i < s.size(); ++i) {
        print(sol.findRepeatedDnaSequences(s[i]));
        cout << endl;
    }

    return 0;
}
