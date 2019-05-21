#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "array/sort/324.wiggle-sort-ii.cpp"

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

//    vector<int> nums1{1, 5, 1, 1, 6, 4};
    vector<int> nums1{1, 3, 2, 2, 3, 1};
//    vector<int> nums1{4, 5, 5, 5, 5, 6, 6, 6};
    s.wiggleSort(nums1);
    print(nums1);
    return 0;
}
