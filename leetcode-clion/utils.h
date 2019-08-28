//
// Created by lt on 2019/8/28.
//

#ifndef LEETCODE_CLION_UTILS_H
#define LEETCODE_CLION_UTILS_H

#include <string>

using namespace std;

/*
 * string
 */

string trim(const string &s) {
    int pos = s.find_first_not_of(" \r\n\t");
    if (pos == string::npos)
        return "";
    int len = s.find_last_not_of(" \r\n\t") - pos + 1;
    return s.substr(pos, len);
}


string quotedString(const string & s) {
    return "\"" + s + "\"";
}


/*
 *  print
 */

template<class T>
void print(const vector<T> &vec) {
    stringstream os;
    os << "[ ";
    for (T val : vec) {
        os << val << ", ";
    }
    os << "]";
    cout << os.str() << endl;
}

#endif //LEETCODE_CLION_UTILS_H
