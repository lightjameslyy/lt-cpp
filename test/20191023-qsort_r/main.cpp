#include <cstdio>
#include <cassert>

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

#include <omp.h>

#include "tools.h"

const size_t kPermSteps = 1000;

using namespace std;
using namespace chrono;

int getDecimalBits(int64_t val) {
    int res = 1;
    while (val /= 10)
        res++;
    return res;
}

void printArray(int* arr, int size) {
    assert(arr != nullptr);
    int dbs = getDecimalBits(size);
    string format = "%-"+to_string(dbs)+"d ";
    for (size_t i = 0; i < size; ++i) {
        printf(format.c_str(), arr[i]);
    }
    printf("\n");
}

static void generateRandom(int** ptr, int low, int high, size_t size) {
    assert(high > low);
    assert(size > 0);
    //default_random_engine dre(system_clock::now().time_since_epoch().count());
    default_random_engine dre(100);
    int* p = new int[size];
    assert(p != nullptr);
    for (size_t i = 0; i < size; ++i) {
        p[i] = low + dre() % (high - low);
    }
    *ptr = p;
}

static void generateRange(int** ptr, int low, int high) {
    assert(high > low);
    size_t size = high - low;
    int* p = new int[size];
    assert(p != nullptr);
    for (size_t i = 0; i < size; ++i) {
        p[i] = low++;
    }
    assert(low == high);
    *ptr = p;
}

int myCmp(const void *a, const void *b, void *arg);

class Data {
  public:
    int* degrees_;
    int* cols_;
    size_t size_;

    explicit Data(size_t size) :size_(size) {
        assert(size_ > 0);
        generateRandom(&degrees_, 0, 10, size_);
        generateRange(&cols_, 0, size_);
    }

    ~Data() {
        delete[] degrees_;
        delete[] cols_;
    }

    void sort() {
        //qsort_r(cols_, size_, sizeof(int), myCmp, this);
        std::sort(cols_, cols_ + size_,
        [&](int i, int j) {
            //if (degrees_[i] == degrees_[j])
            //    return i < j;
            return degrees_[i] < degrees_[j];
        });
    }

    void print() {
        printf("degrees_: \n");
        printArray(degrees_, size_);
        printf("cols_: \n");
        printArray(cols_, size_);
        fflush(stdout);
    }
};

int myCmp(const void *a, const void *b, void *arg) {
    Data* dp = (Data*)arg;
    int v1 = *((int*)a);
    int v2 = *((int*)b);
    //if (dp->degrees_[v1] == dp->degrees_[v2]) {
    //    return v1 - v2;
    //}
    return dp->degrees_[v1] - dp->degrees_[v2];
}

int main(int argc, char *argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    assert(argc == 2);
    size_t size = atol(argv[1]);

    Data data(size);
    printArray(data.degrees_, data.size_);
    printArray(data.cols_, data.size_);
    data.sort();
    printArray(data.cols_, data.size_);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
