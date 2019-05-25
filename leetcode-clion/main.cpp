#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/205.isomorphic-strings.cpp"

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
    cout << s.isIsomorphic("foo", "bar") << endl;
    cout << s.isIsomorphic("egg", "add") << endl;
    cout << s.isIsomorphic("paper", "title") << endl;
    return 0;
}
