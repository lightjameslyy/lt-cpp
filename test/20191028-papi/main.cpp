#include <cstdio>
#include <cassert>

#include <iostream>
#include <vector>
#include <chrono>

#include <omp.h>

#include <papi.h>

#include "tools.h"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    int eventSet = PAPI_NULL;
    long long valor = 0;
    PAPI_library_init(PAPI_VER_CURRENT);
    PAPI_create_eventset(&eventSet);
    PAPI_add_event( eventSet, PAPI_L1_TCM);
    PAPI_start(eventSet);
    PAPI_reset(eventSet);

    /*
    long long int i;
    float pi=0.0;
    for(i=0;i<NUM_PONTOS;i++){
    pi += 4.0/(4.0*i+1.0);
    pi -= 4.0/(4.0*i+3.0);
    }
    */

    int max_val = 0;
    #pragma omp parallel for reduction(max: max_val)
    for (int i = 0; i < 1000; ++i) {
        max_val = i;
    }

    cout << "max_val: " << max_val << endl;
    assert(max_val == 999);

    PAPI_read(eventSet, &valor);
    printf("PAPI_L1_TCM = %llu\n", valor);
    PAPI_stop(eventSet, NULL);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
