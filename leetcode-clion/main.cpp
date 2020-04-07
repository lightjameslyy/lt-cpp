#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "tree/BinaryHeap.cpp"

using namespace std;

typedef BinaryHeap<int, less<int>> MaxHeap;

int main() {
    MaxHeap maxHeap(10, less<int>());
    vector<int> nums{4,3,6,7,42,4,8,1};
    for (int num : nums)
        maxHeap.push_back(num);
    while (!maxHeap.empty()) {
        cout << maxHeap.pop_front() << " ";
    }
    cout << endl;
    return 0;
}

