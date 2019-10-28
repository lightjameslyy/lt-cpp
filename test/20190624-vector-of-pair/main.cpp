#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <random>

typedef std::pair<int, bool> my_pair_t; // pair<location, isMaster>

const int klen = 10;
const int kscope = 100;

int main(int argc, char *argv[]) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed);

    std::vector<my_pair_t> my_pair_vec;
    for (int i = 0; i < klen; ++i) {
        my_pair_vec.push_back(std::make_pair(generator() % kscope, false));
    }
    int masterIndex = generator() % klen;
    std::cout << "masterIndex: " << masterIndex << std::endl;
    my_pair_vec[masterIndex].second = true;
    std::cout << "location:\tisMaster\n";
    for (const auto & kv : my_pair_vec) {
        std::cout << kv.first << ":\t\t" << kv.second << std::endl;
    }
    return 0;
}
