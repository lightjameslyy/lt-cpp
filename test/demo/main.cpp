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

    printf("hello world.\n");

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
