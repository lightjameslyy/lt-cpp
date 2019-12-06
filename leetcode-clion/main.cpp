#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/basic/204.count-primes.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<int> n = {10};
    for (int i = 0; i < n.size(); ++i) {
        cout << sol.countPrimes(n[i]) << endl;
    }

    return 0;
}

