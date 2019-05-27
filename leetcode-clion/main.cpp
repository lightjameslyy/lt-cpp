#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "string/basics/49.group-anagrams.cpp"

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
    string strs[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> res = s.groupAnagrams(vector<string>(strs, strs+6));
    for (auto v : res) {
        print(v);
    }
    return 0;
}
