#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
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

    omp_set_nested(1);

    #pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num();
        printf("id: %d, num_threads: %d\n", tid, omp_get_num_threads());
        #pragma omp parallel for if (tid%2) num_threads(5)
        for (int i = 0; i < 5; ++i) {
            printf("nested... id: %d:%d, num_threads: %d\n", tid, omp_get_thread_num(), omp_get_num_threads());
        }
    }

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
