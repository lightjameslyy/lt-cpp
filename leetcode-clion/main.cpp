#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/273.integer-to-english-words.cpp"

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
//    cout << "\"" << s.decode(130, 0) << "\"" << endl;
    cout << "\"" << s.numberToWords(0) << "\"" << endl;
    cout << "\"" << s.numberToWords(19) << "\"" << endl;
    cout << "\"" << s.numberToWords(123) << "\"" << endl;
    cout << "\"" << s.numberToWords(12345) << "\"" << endl;
    cout << "\"" << s.numberToWords(1234567) << "\"" << endl;
    cout << "\"" << s.numberToWords(1234567891) << "\"" << endl;
    return 0;
}
