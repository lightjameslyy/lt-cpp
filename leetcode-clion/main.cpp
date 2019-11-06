#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/165.compare-version-numbers.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<string> version1 = {
            "0.1",
            "1.0.1",
            "7.5.2.4",
            "1.01",
            "1.0",
            "1.1",
            "1.2"
    };
    vector<string> version2 = {
            "1.1",
            "1",
            "7.5.3",
            "1.001",
            "1.0.0",
            "1.10",
            "1.10"
    };
    for (int i = 0; i < version1.size(); ++i) {
        cout << sol.compareVersion(version1[i], version2[i]) << endl;
    }

    return 0;
}
