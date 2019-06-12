#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
    vector<unordered_map<int,bool>> vm(4);
    for (int i = 0; i < 4; ++i) {
        vm[i][1] = 1;
        vm[i][2] = 0;
    }
    for (auto &m : vm) {
        for (auto & kv : m) {
            cout << kv.first << ": " << kv.second << endl;
        }
        cout << endl;
    }
    return 0;
}
