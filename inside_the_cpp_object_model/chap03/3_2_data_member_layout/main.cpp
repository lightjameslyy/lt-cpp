#include <cassert>
#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"

using namespace std;
using namespace chrono;


// reference: icom chapter 3.2

namespace test_3_2_1 {

struct Point3D {
    float x;
    float y;
    static const int chunkSize = 250;
    float z;
};

template<class class_type, class data_type1, class data_type2>
void access_order(data_type1 class_type::*mem1, data_type2 class_type::*mem2) {
    assert(mem1 != mem2);
    printf("mem1:%p, mem2:%p\n", mem1, mem2);
}

void test() {
    printf("y:mem1, z:mem2\n");
    access_order(&Point3D::y, &Point3D::z);
}
} // namespace test_3_2_1

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    printf("test_3_2_1 +++\n");
    test_3_2_1::test();
    printf("test_3_2_1 ---\n");

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
