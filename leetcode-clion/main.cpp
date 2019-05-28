#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/87.scramble-string.cpp"

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
    cout << s.isScramble("great", "rgeat") << endl;
    cout << s.isScramble("abcde", "caebd") << endl;
    return 0;
}
