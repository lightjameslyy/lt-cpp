#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "math/sum/1.two-sum.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<int> nums = {2, 7, 11, 15};
    print(sol.twoSum(nums, 9));

    return 0;
}

