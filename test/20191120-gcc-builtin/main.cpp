#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <cassert>
#include <chrono>

#include "../tools.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    /*
     *
     * __builtin_popcount: number of 1 bits;
     * __builtin_clz: number of leading zeros;
     * __builtin_ctz: number of tailing zeros;
     * __builtin_ffs: (index of least significant 1 bit) + 1;
     */

    // 00000000 00000000 00000000 00001000
    unsigned int a = 8;
    printf("a: %08x\n", a);
    assert(__builtin_popcount(a) == 1);
    assert(__builtin_clz(a) == 28);
    assert(__builtin_ctz(a) == 3);
    assert(__builtin_ffs(a) == 4);

    // 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000101
    unsigned long b = 5;
    printf("b: %016lx\n", b);
    assert(__builtin_popcountl(b) == 2);
    assert(__builtin_clzl(b) == 61);
    assert(__builtin_ctzl(b) == 0);
    assert(__builtin_ffsl(b) == 1);

    // 00000000 00000000 00000000 00000000 00000000 00000000 00000000 11111111
    unsigned long long c = 255;
    printf("c: %016llx\n", c);
    assert(__builtin_popcountll(c) == 8);
    assert(__builtin_clzll(c) == 56);
    assert(__builtin_ctzll(c) == 0);
    assert(__builtin_ffsll(c) == 1);

    // 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
    unsigned long long z = 0;
    printf("z: %016llx\n", z);
    assert(__builtin_popcountll(z) == 0);
    cout << __builtin_clzll(z) << endl;
    cout << __builtin_ctzll(z) << endl;
    //assert(__builtin_clzll(z) == 64);     // undefined
    //assert(__builtin_ctzll(z) == 64);     // undefined
    assert(__builtin_ffsll(z) == 0);

    // 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
    unsigned long long u = 0x8000000000000000;
    printf("u: %016llx\n", u);
    assert(__builtin_popcountll(u) == 1);
    assert(__builtin_clzll(u) == 0);
    assert(__builtin_ctzll(u) == 63);
    assert(__builtin_ffsll(u) == 64);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
