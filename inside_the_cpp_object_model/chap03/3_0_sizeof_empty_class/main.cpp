#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"

using namespace std;
using namespace chrono;


// reference: icom chapter 3.0

namespace test_3_0_1 {

struct A {};
struct B : public virtual A {};
struct C : public virtual A {};
struct D : public B, public C {};

void test() {
    printf("sizeof A: %d\n", sizeof(A));
    printf("sizeof B: %d\n", sizeof(B));
    printf("sizeof C: %d\n", sizeof(C));
    printf("sizeof D: %d\n", sizeof(D));
}
} // namespace test_3_0_1

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    printf("test_3_0_1 +++\n");
    test_3_0_1::test();
    printf("test_3_0_1 ---\n");

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
