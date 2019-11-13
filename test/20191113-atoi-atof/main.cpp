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

    int a = atoi("12 jgjh0903");
    double b = atof("3.14159265 joa");
    int c = atoi("2019klkaj");
    double d = atof("1.134joa");

    printf("a=%d\n", a);
    printf("b=%.10f\n", b);
    printf("c=%d\n", c);
    printf("d=%.10f\n", d);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
