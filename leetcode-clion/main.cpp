#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/168.excel-sheet-column-title.cpp"

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
    cout << s.convertToTitle(701) << endl;
    cout << s.convertToTitle(28) << endl;
    cout << s.convertToTitle(4798234) << endl;
    cout << s.convertToTitle(52) << endl;
    return 0;
}
