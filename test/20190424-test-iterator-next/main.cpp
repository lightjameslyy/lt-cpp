#include <iostream>
#include <cstdint>
#include <unordered_map>

using namespace std;


const int64_t RANDOM_MAX = 1000;

int main(int argc, char* argv[]) {
    unordered_map<int, int> mp {
        {1, 1},
        {8, 1},
        {2, 1},
        {7, 1},
        {117, 1}
    };

    for (auto const& elem : mp) {
        cout << elem.first << ", " << elem.second << endl;
    }

    auto const& third_elem = next(mp.begin(), 2);
    cout << "third: " << third_elem->first << ", " << third_elem->second << endl;
    return 0;
}
