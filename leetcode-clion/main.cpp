#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "array/sort/75.sort-colors.cpp"

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
//    vector<int> nums1{2, 0, 2, 1, 1, 0};
//    vector<int> nums1{2, 0, 1};
    vector<int> nums1{0, 0};
//    vector<int> nums1{2, 2};
    s.sortColors(nums1);
    print(nums1);
    return 0;
}
