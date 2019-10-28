#include <iostream>
#include <chrono>
#include <random>
#include <cstdint>

using namespace std;


const int64_t RANDOM_MAX = 1000;

int main(int argc, char* argv[]) {
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937_64 generator(seed);

    cout << "random int64 using mt19937_64: " << generator()%RANDOM_MAX << endl;
    return 0;
}
