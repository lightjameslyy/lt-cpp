#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/316.remove-duplicate-letters.cpp"

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
    cout << s.removeDuplicateLetters("cbacdcbc") << endl;
    cout << s.removeDuplicateLetters("bcabc") << endl;
    cout << s.removeDuplicateLetters("thesqtitxyetpxloeevdeqifkz") << endl;
    return 0;
}
