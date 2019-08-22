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

#pragma omp parallel 
{
    printf("parallel code1\n");
#pragma omp single
    {
        printf("single1\n");
    }
#pragma omp single
    {
        printf("single2\n");
    }
#pragma omp single
    {
        printf("single3\n");
    }
#pragma omp single
    {
        printf("single4\n");
    }
    printf("parallel code2\n");
#pragma omp single
    {
        printf("single5\n");
    }
#pragma omp single
    {
        printf("single6\n");
    }
#pragma omp single
    {
        printf("single7\n");
    }
#pragma omp single
    {
        printf("single8\n");
    }
}

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
