#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <cassert>
#include <cstring>

#include "tools.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    size_t dataSize = 1LL << 27;
    cout << "data size: " << to_string(dataSize * sizeof(long long) / (double)(1LL << 30)) << "GB" << endl;

    //long long* data_aligned = (long long*) alloc_4k_aligned_mem(dataSize * sizeof(long long), &orig);
    long long* data_aligned;
    int ret = posix_memalign((void**)&data_aligned, 64, dataSize * sizeof(long long));
    if (ret) {
        fprintf(stderr, "posix_memalign failed: %s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    cout << "data_aligned: " << data_aligned << endl;

    for (int n = 0; n < 4; ++n) {
        auto start = system_clock::now();

        //memset(data_aligned, 0, dataSize * sizeof(long long));
        for (size_t i = 0; i < dataSize; ++i) {
            data_aligned[i] = i;
        }

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "4k aligned time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    }

    long long* data_not_aligned = (long long*)malloc(dataSize * sizeof(long long));
    if (data_not_aligned == nullptr) {
        fprintf(stderr, "malloc failed ...\n");
        exit(EXIT_FAILURE);
    }

    cout << "data_not_aligned: " << data_not_aligned << endl;

    for (int n = 0; n < 4; ++n) {
        auto start = system_clock::now();

        //memset(data_not_aligned, 0, dataSize * sizeof(long long));
        for (size_t i = 0; i < dataSize; ++i) {
            data_not_aligned[i] = i;
        }

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "4k not aligned time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    }   // for n

    free(data_aligned);
    free(data_not_aligned);
    return 0;
}
