#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"

#define M 32
#define N 60000000

using namespace std;
using namespace chrono;

void func(int i, vector<vector<int> > &data) {
    for (int j=1; j<N; ++j) {
        data[i][j] = data[i][j-1] + data[i][j];
    }
}

int main(int argc, char *argv[]) {
    vector<vector<int> > data(M, vector<int>(N, 1));

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

#pragma omp parallel shared(data) 
{
#pragma omp sections
    {
#pragma omp section
    func(0, data);
#pragma omp section
    func(1, data);
#pragma omp section
    func(2, data);
#pragma omp section
    func(3, data);
#pragma omp section
    func(4, data);
#pragma omp section
    func(5, data);
#pragma omp section
    func(6, data);
#pragma omp section
    func(7, data);
#pragma omp section
    func(8, data);
#pragma omp section
    func(9, data);
#pragma omp section
    func(10, data);
#pragma omp section
    func(11, data);
#pragma omp section
    func(12, data);
#pragma omp section
    func(13, data);
#pragma omp section
    func(14, data);
#pragma omp section
    func(15, data);
#pragma omp section
    func(16, data);
#pragma omp section
    func(17, data);
#pragma omp section
    func(18, data);
#pragma omp section
    func(19, data);
#pragma omp section
    func(20, data);
#pragma omp section
    func(21, data);
#pragma omp section
    func(22, data);
#pragma omp section
    func(23, data);
#pragma omp section
    func(24, data);
#pragma omp section
    func(25, data);
#pragma omp section
    func(26, data);
#pragma omp section
    func(27, data);
#pragma omp section
    func(28, data);
#pragma omp section
    func(29, data);
#pragma omp section
    func(30, data);
#pragma omp section
    func(31, data);
    }
}

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
