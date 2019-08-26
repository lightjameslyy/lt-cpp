#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/171.excel-sheet-column-number.cpp"

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
    cout << s.titleToNumber("A") << endl;
    cout << s.titleToNumber("AB") << endl;
    cout << s.titleToNumber("ZY") << endl;
    cout << s.titleToNumber("AZ") << endl;
    cout << s.titleToNumber("CFDGSXM") << endl;
    return 0;
}
