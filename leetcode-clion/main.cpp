#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/advanced/68.text-justification.cpp"

using namespace std;

template<class T>
void print(const vector<T> &vec) {
    stringstream os;
//    os << "[ ";
    for (T val : vec) {
        os << "\"" << val << "\",\n";
    }
//    os << "]";
    cout << os.str() << endl;
}

int main() {
    Solution s;
//    cout << "\"" << s.decode(130, 0) << "\"" << endl;
    vector<string> vs = {"This", "is", "an", "example", "of", "text", "justification."};
    print(s.fullJustify(vs, 16));

    vs = {"What","must","be","acknowledgment","shall","be"};
    print(s.fullJustify(vs, 16));

    vs = {"Science","is","what","we","understand","well","enough","to","explain", "to","a","computer.","Art","is",
          "everything","else","we","do"};
    print(s.fullJustify(vs, 20));

    vs = {"a"};
    print(s.fullJustify(vs, 2));
    return 0;
}
