#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/28.implement-strstr.cpp"

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
    cout << s.strStr("hello", "ll") << endl;
    cout << s.strStr("", "") << endl;
    cout << s.strStr("aaaaa", "bba") << endl;
    cout << s.strStr("bbc abcdab abcdabcdabde", "abcdabd") << endl;
    return 0;
}
