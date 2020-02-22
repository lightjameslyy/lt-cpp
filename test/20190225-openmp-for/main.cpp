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

    int workLoads[8][10];
    int workPos[8] = {0};

    #pragma omp parallel for num_threads(8)
    for (int i = 0; i < 50; ++i) {
        workLoads[omp_get_thread_num()][workPos[omp_get_thread_num()]++] = i;
    }

    for (int i = 0; i < 8; ++i) {
        printf("tid: %d, i: ", i);
        for (int j = 0; j < workPos[i]; ++j)
            printf("%d, ", workLoads[i][j]);
        printf("\n");
    }

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
