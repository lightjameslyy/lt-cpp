#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"

using namespace std;
using namespace chrono;


// reference: icom chapter 2.3

// explicit initialization
namespace test_2_3_1 {
struct X {
    X() {
        printf("X default constructor\n");
    }
    X(const X&) {
        printf("X copy constructor\n");
    }
    ~X() {
        printf("X destructor\n");
    }
};

void test() {
    X x0;
    X x1(x0);
    X x2 = x0;
    X x3 = X{x0};
}
} // namespace test_2_3_1

// argument initialization
namespace test_2_3_2 {
struct Y {
    Y() {
        printf("Y default constructor\n");
    }
    Y(const Y&) {
        printf("Y copy constructor\n");
    }
    ~Y() {
        printf("Y destructor\n");
    }
};

void foo(Y y) {
    printf("execute foo...\n");
}

void test() {
    Y y0;
    foo(y0);
}
} // namespace test_2_3_2

// return value initialization
namespace test_2_3_3 {
struct Z {
    Z() {
        printf("Z default constructor\n");
    }
    Z(const Z&) {
        printf("Z copy constructor\n");
    }
    ~Z() {
        printf("Z destructor\n");
    }
    int val;
};

Z* inptr;

// returned value optimization
// void foo( Z& __result) { ... }
Z foo(int a) {
    Z z;
    inptr = &z;
    z.val = a;
    return z;
}

void test() {
    // no copy constructor called in foo()
    Z z0 = foo(10);
    Z* outptr = &z0;
    printf("inptr %s outptr\n", (inptr == outptr) ? "=" : "!=");
    // copy constructor called here
    Z z1 = z0;
}
} // namespace test_2_3_3

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    printf("test_2_3_1 +++\n");
    test_2_3_1::test();
    printf("test_2_3_1 ---\n");
    printf("test_2_3_2 +++\n");
    test_2_3_2::test();
    printf("test_2_3_2 ---\n");
    printf("test_2_3_3 +++\n");
    test_2_3_3::test();
    printf("test_2_3_3 ---\n");

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
