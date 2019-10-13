#include <cstdio>
#include <cassert>

#include <iostream>
#include <vector>
#include <chrono>

#include <omp.h>

#include "tools.h"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    int max_val = 0;
    #pragma omp parallel for reduction(max: max_val)
    for (int i = 0; i < 1000; ++i) {
        max_val = i;
    }

    cout << "max_val: " << max_val << endl;
    assert(max_val == 999);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
