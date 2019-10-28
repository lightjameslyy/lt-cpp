#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

struct queryInfo {
    int vcolumnID;
    int queryPE;
};

int main() {
    vector<queryInfo> qis;
    qis.push_back({1, 1});
    qis.push_back({2, 1});
    for (auto &qi : qis) {
        cout << qi.vcolumnID << ", " << qi.queryPE << endl;
    }
    return 0;
}
