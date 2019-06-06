#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/6.zigzag-conversion.cpp"

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
    cout << s.convert("PAYPALISHIRING", 3) << endl;
    cout << s.convert("PAYPALISHIRING", 4) << endl;
    return 0;
}
