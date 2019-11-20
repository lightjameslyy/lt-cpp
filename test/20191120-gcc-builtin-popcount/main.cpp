#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <cassert>
#include <chrono>

#include "tools.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    unsigned int a = 8;
    printf("a: %x\n", a);
    assert(__builtin_popcount(a) == 1);

    unsigned long b = 5;
    printf("b: %x\n", b);
    assert(__builtin_popcountl(b) == 2);

    unsigned long long c = 255;
    printf("c: %x\n", c);
    assert(__builtin_popcountll(c) == 8);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
