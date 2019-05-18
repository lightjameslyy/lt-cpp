#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "array/sort/88.merge-sorted-array.cpp"

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
    vector<int> nums1 {1,2,3,0,0,0};
    vector<int> nums2 {2,5,6};
    s.merge(nums1, 3, nums2, 3);
    print(nums1);
    return 0;
}
