#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/344.reverse-string.cpp"

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
    vector<char> v1{'0', '1', '2', '3', '4'};
    s.reverseString(v1);
    print<char>(v1);

    vector<char> v2{'0', '1', '2', '3', '4', '5'};
    s.reverseString(v2);
    print<char>(v2);
    return 0;
}
