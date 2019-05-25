#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/151.reverse-words-in-a-string.cpp"

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
//    string res = s.reverseWords("a good   example");
//    string res = s.reverseWords("  hello world!  ");
//    string res = s.reverseWords("the sky is blue");
    string res = s.reverseWords("   one.   +two three?   ~four   !five- ");
    cout << "\"" << res << "\"" << endl;
    return 0;
}
