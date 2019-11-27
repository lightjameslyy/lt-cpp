#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>
#include <cassert>
#include <sstream>
#include <cstring>

#include "tools.h"

using namespace std;
using namespace chrono;

template <class T>
void printVector(vector<T> nums, size_t len, const string& name) {
    ostringstream oss;
    oss << name << ": [";
    for (size_t i = 0; i < len; ++i) {
        oss << nums[i] << ", ";
    }
    oss << "]";
    printf("%s\n", oss.str().c_str());
}

vector<long long> getWorkLoads(long long dataSize, int nTasks) {
    vector<long long> workLoads(nTasks + 1, 0);
    long long minBlocks = dataSize / nTasks;
    long long more = dataSize % nTasks;
    for (int i = 1; i <= nTasks; ++i) {
        workLoads[i] = workLoads[i - 1] + minBlocks + (more-- > 0 ? 1 : 0);
    }
    return workLoads;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "need argument scale.\n");
        exit(-1);
    }

    int scale = atoi(argv[1]);
    assert(scale >= 0 && scale < 30);

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    // 2^30 bits ==> 2^24 long long
    long long dataSize = 1LL << scale;
    long long* data = new long long[dataSize];
    cout << "data size: " << to_string(dataSize * sizeof(long long) / (double)(1LL << 30)) << "GB" << endl;

    int nProcs = omp_get_num_procs();
    for (int nThreads = 1; nThreads <= nProcs; ++nThreads) {
        int nTasks = 2 * nThreads;
        vector<long long> workLoads = getWorkLoads(dataSize, nTasks);
        //printVector<long long>(workLoads, nThreads + 1, "workLoads");
        omp_set_num_threads(nThreads);
        auto start = system_clock::now();

        #pragma omp parallel for
        for (int i = 0; i < nTasks; ++i) {
            //int tid = omp_get_thread_num();
            //printf("tid:%d, task:%d\n", tid, i);
            memset(&data[workLoads[i]], nThreads, sizeof(long long) * (workLoads[i + 1] - workLoads[i]));
        }

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << to_string(nThreads) << " threads, time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    }

    delete [] data;
    return 0;
}
