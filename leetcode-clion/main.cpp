#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/345.reverse-vowels-of-a-string.cpp"

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
//    string res = s.reverseVowels("leetcode");
//    string res = s.reverseVowels("OE");
    string res = s.reverseVowels(",.");
    cout << "\"" << res << "\"" << endl;
    return 0;
}
