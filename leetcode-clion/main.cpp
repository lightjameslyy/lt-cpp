#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "array/counter/228.summary-ranges.cpp"

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
    vector<int> nums1{0, 1, 2, 4, 5, 7};
    vector<string> res = s.summaryRanges(nums1);
    print<string>(res);
//    vector<int> nums2{0, 2, 3, 4, 6, 8, 9};
    vector<int> nums2{int(-2147483648), int(-2147483647), int(2147483647)};
    res = s.summaryRanges(nums2);
    print<string>(res);
    cout << INT_MAX << " " << INT_MIN << endl;
    return 0;
}
