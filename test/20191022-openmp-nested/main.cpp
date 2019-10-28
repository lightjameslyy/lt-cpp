#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {
    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    omp_set_nested(1);

    #pragma omp parallel num_threads(2)
    {
        printf("id: %d, num_threads: %d\n", omp_get_thread_num(), omp_get_num_threads());
        #pragma omp parallel num_threads(5)
        {
            size_t sum = 0;
            printf("nested... id: %d, num_threads: %d\n", omp_get_thread_num(), omp_get_num_threads());
            for (size_t i = 0; i < (1LL<<30); ++i) {
                sum += i;
            }
        }
    }

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
