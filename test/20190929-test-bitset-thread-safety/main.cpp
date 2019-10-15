#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>
#include <bitset>

#include "tools.h"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    const int numVertices = 100;
    bitset<numVertices> visited;

    #pragma omp parallel for
    for (int i = 0; i < numVertices; ++i) {
        if (i % 2) {
            visited.set(i);
        }
    }

    cout << "visited count: " << visited.count() << endl;

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
