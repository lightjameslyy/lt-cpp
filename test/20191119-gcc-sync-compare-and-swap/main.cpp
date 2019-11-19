#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <cassert>
#include <chrono>
#include <thread>

#include "tools.h"

using namespace std;
using namespace chrono;

void thread_func(int* a) {
    int oldval, newval;
    for (int i = 0; i < 10; ++i) {
        do {
            oldval = *a;
            newval = oldval + 1;
        } while(!__sync_bool_compare_and_swap(a, oldval, newval));
    }
}

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    int threadNum = thread::hardware_concurrency();
    int a = 0;
    vector<thread> workers;
    for (int i = 0; i < threadNum; ++i) {
        workers.push_back(thread(thread_func, &a));
    }

    for (auto& worker : workers) {
        worker.join();
    }
    assert(a == threadNum * 10);
    printf("a: %d\n", a);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
