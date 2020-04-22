#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"

using namespace std;
using namespace chrono;


// 默认构造函数
// reference: https://zh.cppreference.com/w/cpp/language/default_constructor
namespace test_2_1_0 {
struct A {
    int x;
    A(int x = 1): x(x) {
        printf("constructor A.\n");
    } // 用户定义默认构造函数
};

struct B: A {
    // 隐式定义 B::B()，调用 A::A()
};

struct C {
    A a;
    // 隐式定义 C::C()，调用 A::A()
};

struct D: A {
    D(int y): A(y) {}
    // 不会声明 D::D()，因为存在另一构造函数
};

struct E: A {
    E(int y): A(y) {}
    E() = default; // 显式预置，调用 A::A()
};

struct F {
    int& ref; // 引用成员
    const int c; // const 成员
    // F::F() 被隐式定义为弃置
};

struct G: F {
    // G::G() 被隐式定义为弃置
};

struct H {
    ~H() = delete;
};

struct I: H {
    // I::I() 被隐式定义为弃置
};

void test() {
    printf("test_2_1_0 begins...\n");
    A a;
    B b;
    C c;
    // D d; // 编译错误
    D d(1);
    E e;
    // F f; // 编译错误
    G g;
    // H h; // 编译错误
    // I i; // 编译错误
    printf("test_2_1_0 ends...\n");
}
} // namespace test_2_1_0

namespace test_2_1_1 {

struct A {
    A() {
        printf("construct A\n");
    }
};

struct B {
    B() {
        printf("construct B\n");
    }
};

struct C {
    C() {
        printf("construct C\n");
    }
};

// 类的成员有默认构造函数
struct D {
    A a;
    B b;
    C c;
    D() {
        printf("construct D\n");
    }
};

// 基类有默认构造函数
struct E: A, B, C {
    E() {
        printf("construct E\n");
    }
};

void test() {
    printf("test_2_1_1 begins...\n");
    D d;
    E e;
    printf("test_2_1_1 ends...\n");
}
} // namespace test_2_1_1

namespace test_2_1_2 {
// 成员函数有虚函数
struct A {
    virtual void f() {
        printf("A f()\n");
    }
};

// 基类有虚基类
struct B: virtual A {
};

void test() {
    printf("test_2_1_2 begins...\n");
    A a;
    B b;
    printf("test_2_1_2 ends...\n");
}

} // namespace test_2_1_2

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    test_2_1_0::test();
    test_2_1_1::test();
    test_2_1_2::test();

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
