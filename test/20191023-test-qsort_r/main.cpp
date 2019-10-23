#include <cstdio>
#include <cassert>

#include <iostream>
#include <vector>
#include <chrono>

#include <omp.h>

#include "tools.h"

using namespace std;
using namespace chrono;

int myCmp(const void *a, const void *b, void *arg);

class Data {
  public:
    int* degrees_;
    int* cols_;
    int size_;

    explicit Data() {
        size_ = 10;
        degrees_ = new int[size_] {3,4,0,5,2,1,1,3,0,8};
        assert(degrees_ != nullptr);
        cols_ = new int[size_] {0,1,2,3,4,5,6,7,8,9};
        assert(cols_ != nullptr);
    }

    ~Data() {
        delete[] degrees_;
        delete[] cols_;
    }

    void sort() {
        qsort_r(cols_, size_, sizeof(int), myCmp, this);
    }

    void print() {
        printf("degrees_: \n");
        for (size_t i = 0; i < size_; ++i) {
            printf("%d:%d ", i, degrees_[i]);
        }
        printf("\ncols_: \n");
        for (size_t i = 0; i < size_; ++i) {
            printf("%d:%d ", i, cols_[i]);
        }
        printf("\n");
        fflush(stdout);
    }
};

int myCmp(const void *a, const void *b, void *arg) {
    Data* dp = (Data*)arg;
    int v1 = *((int*)a);
    int v2 = *((int*)b);
    if (dp->degrees_[v1] == dp->degrees_[v2]) {
        return v1 - v2;
    }
    return dp->degrees_[v1] - dp->degrees_[v2];
}

int main(int argc, char *argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    Data data;
    data.print();
    data.sort();
    data.print();

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
