#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int a = 0;

template<class T>
void print(vector<T> list) {
    ostringstream os;
    os << "[ ";
    for (auto val: list) {
        os << val << ", ";
    }
    os << "]\n";
    cout << os.str();
}

int gdb_test() {
    return ++a;
}

int main() {
    vector<int> nums {2, 34, 5, 6, 8};
    print(nums);
    for (int i = 0; i <= nums.size(); ++i) {
        cout << nums[i] << endl;
    }
    return 0;
}
