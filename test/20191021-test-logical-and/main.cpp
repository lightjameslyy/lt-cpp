#include <cstdio>
#include <cassert>

#include <iostream>
#include <vector>
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

    int a = 1, b = 0;

    if (a != -1 && b != 0) {
        printf("case 1\n");
    } else {
        printf("case 2\n");
    }

    if ((a != -1) && (b != 0)) {
        printf("case 1\n");
    } else {
        printf("case 2\n");
    }

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
