#include <cassert>
#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"

using namespace std;
using namespace chrono;


// reference: icom chapter 3.6

// offset and address of data member
namespace test_3_6_1 {

struct Point3d {
    virtual ~Point3d() {}
    static Point3d origin;
    int x, y, z;
};

Point3d Point3d::origin;

void test() {

    printf("&Point3d::x = %p\n", &Point3d::x);
    printf("&Point3d::y = %p\n", &Point3d::y);
    printf("&Point3d::z = %p\n", &Point3d::z);

    printf("&Point3d::origin = %p\n", &Point3d::origin);
    printf("&Point3d::origin.x = %p\n", &Point3d::origin.x);
    printf("&Point3d::origin.y = %p\n", &Point3d::origin.y);
    printf("&Point3d::origin.z = %p\n", &Point3d::origin.z);
}
} // namespace test_3_6_1

namespace test_3_6_2 {
struct A {
    int a;
};
struct B {
    int b;
};
struct C : A, B {
    int c;
};

void test() {
    printf("&A::a = %p\n", &A::a);
    printf("&B::b = %p\n", &B::b);
    printf("&C::a = %p\n", &C::a);
    printf("&C::b = %p\n", &C::b);
    printf("&C::c = %p\n", &C::c);
}
} // namespace test_3_6_2

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    printf("test_3_6_1 +++\n");
    test_3_6_1::test();
    printf("test_3_6_1 ---\n");

    printf("test_3_6_2 +++\n");
    test_3_6_2::test();
    printf("test_3_6_2 ---\n");

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
