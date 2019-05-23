#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/14.longest-common-prefix.cpp"

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
    vector<string> strs{"flower", "flow", "flight"};
    cout << s.longestCommonPrefix(strs);
    return 0;
}
