#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>
#include <cassert>
#include <cstring>

#include "tools.h"

#define ALIGNED_BASE 0x1000

using namespace std;
using namespace chrono;

static void* alloc_4k_aligned_mem(size_t size, void** ppOut) {
    *ppOut = (void*) calloc(1, size + ALIGNED_BASE - 1);
    printf("ppOut: %p\n", *ppOut);
    if(!ppOut) {
        return NULL;
    }

    void* pAligned = (void*)((uintptr_t)(*ppOut + ALIGNED_BASE - 1) & ~(ALIGNED_BASE - 1));
    printf("pAligned: %p\n", pAligned);
    return pAligned;
}

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    void* orig;
    size_t dataSize = 1LL << 27;
    cout << "data size: " << to_string(dataSize * sizeof(long long) / (double)(1LL << 30)) << "GB" << endl;

    long long* data_aligned = (long long*) alloc_4k_aligned_mem(dataSize * sizeof(long long), &orig);
    assert(orig);
    long long* data_not_aligned = (long long*)orig;

    for (int n = 0; n < 4; ++n) {
#ifdef LT_TEST_ALIGNED
        auto start = system_clock::now();

        //memset(data_aligned, 0, dataSize * sizeof(long long));
        for (size_t i = 0; i < dataSize; ++i) {
            data_aligned[i] = i;
        }

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "4k aligned time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
#else

        auto start = system_clock::now();

        //memset(data_not_aligned, 0, dataSize * sizeof(long long));
        for (size_t i = 0; i < dataSize; ++i) {
            data_not_aligned[i] = i;
        }

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "4k not aligned time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
#endif  // LT_TEST_ALIGNED
    }   // for n

    free(orig);
    return 0;
}
