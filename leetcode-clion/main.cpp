#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/38.count-and-say.cpp"

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
    cout << s.countAndSay(10) << endl;
    return 0;
}
