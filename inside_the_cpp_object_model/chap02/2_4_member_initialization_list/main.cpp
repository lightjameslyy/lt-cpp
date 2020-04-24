#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"

using namespace std;
using namespace chrono;


// reference: icom chapter 2.4

namespace test_2_4_1 {

struct X {
    int i, j;
    X(int val): j(val), i(j) {} // pitfalls
};

struct Y {
    int i, j;
    Y(int val): j(val) {
        i = j;   // right
    }
};

void test() {
    X* x = new X(3);
    Y* y = new Y(4);

    printf("x.i = %d, x.j = %d\n", x->i, x->j); // 堆区，不确定值
    printf("y.i = %d, y.j = %d\n", y->i, y->j);

    delete x;
    delete y;

    X x1(5);
    Y y1(6);

    printf("x1.i = %d, x1.j = %d\n", x1.i, x1.j);   // 栈区，零初始化
    printf("y1.i = %d, y1.j = %d\n", y1.i, y1.j);

}
} // namespace test_2_4_1

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    printf("test_2_4_1 +++\n");
    test_2_4_1::test();
    printf("test_2_4_1 ---\n");

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
