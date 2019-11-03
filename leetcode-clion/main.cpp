#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "string/parentheses/241.different-ways-to-add-parentheses.cpp"

using namespace std;

int main() {
    Solution s;
    vector<string> input = {
            "",
            "1",
            "2-1-2",
            "2*3-4*5"
    };
    for (int i = 0; i < input.size(); ++i) {
        print(s.diffWaysToCompute(input[i]));
        cout << endl;
    }

    return 0;
}
