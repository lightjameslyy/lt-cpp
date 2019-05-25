#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/383.ransom-note.cpp"

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
    cout << s.canConstruct("aa", "aab") << endl;
    cout << s.canConstruct("a", "b") << endl;
    cout << s.canConstruct("aa", "ab") << endl;
    return 0;
}
