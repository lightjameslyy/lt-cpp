#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>
#include <atomic>

#include "tools.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    if (argc < 3) {
        printf("Usage: \n./<exefile> <nThreads> <taskScale>\n");
        exit(EXIT_FAILURE);
    }

    int nThreads = atoi(argv[1]);
    int taskScale = atoi(argv[2]);

    omp_set_num_threads(nThreads);
    size_t nTasks = 1LL << taskScale;

    auto start = system_clock::now();

    atomic<size_t> nextTask1(0);
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        while(true) {
            size_t nextId = nextTask1.fetch_add(1);
            if (nextId >= nTasks) {
                break;
            }
        }
    }
    printf("nextTask1: %lu\n", nextTask1.load());

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "std::atomic time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n\n";

    start = system_clock::now();

    size_t nextTask2 = 0;
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        while(true) {
            size_t nextId = __atomic_fetch_add(&nextTask2, 1, __ATOMIC_SEQ_CST);
            if (nextId >= nTasks) {
                break;
            }
        }
    }
    printf("nextTask2: %lu\n", nextTask2);

    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "gcc-builtin __atomic time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n\n";

    start = system_clock::now();

    size_t nextTask3 = 0;
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        while(true) {
            size_t nextId = __sync_fetch_and_add(&nextTask3, 1);
            if (nextId >= nTasks) {
                break;
            }
        }
    }
    printf("nextTask3: %lu\n", nextTask3);

    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "gcc-builtin __sync time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n\n";
    return 0;
}
