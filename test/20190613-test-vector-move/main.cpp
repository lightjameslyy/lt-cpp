#include <vector>
#include <iostream>

using namespace std;

struct queryInfo {
    int vcolumnID;
    int queryPE;
};

static void print(vector<queryInfo> &list) {
    for (auto &qi: list) {
        cout << qi.vcolumnID << ", " << qi.queryPE << endl;
    }
    cout << endl;
}

int main() {
    vector<queryInfo> qis;
    qis.push_back({1, 1});
    qis.push_back({2, 1});

    vector<queryInfo> qis1(move(qis));

    cout << "qis: \n";
    print(qis);
    cout << "qis1: \n";
    print(qis1);
    return 0;
}
