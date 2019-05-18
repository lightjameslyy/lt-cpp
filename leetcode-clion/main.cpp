#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "array/sort/283.move-zeroes.cpp"

using namespace std;

template<class T>
void print(vector<T> &vec) {
    stringstream os;
    os << "[ ";
    for (T val : vec) {
        os << val << ", ";
    }
    os << "]";
    cout << os.str() << endl;
}

int main() {
    Solution s;
    vector<int> nums1{0, 1, 0, 3, 12};
    s.moveZeroes(nums1);
    print(nums1);
    return 0;
}
