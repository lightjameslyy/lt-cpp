#include <cstdio>
#include <cassert>

#include <iostream>
#include <vector>
#include <chrono>

#include <omp.h>

#include "tools.h"

using namespace std;
using namespace chrono;

typedef struct packed_edge_t {
    uint32_t v0;
    uint32_t v1;
} packed_edge_t;

typedef union packed_edge {
    uint64_t val;
    packed_edge_t edge;
} packed_edge;

int main(int argc, char *argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    packed_edge pe;
    pe.edge.v0 = 0;
    pe.edge.v1 = 1;
    cout << pe.val << endl;
    assert((pe.val >> 32) == 1);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
