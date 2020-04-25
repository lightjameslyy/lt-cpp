#include <cassert>
#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"

using namespace std;
using namespace chrono;


// reference: icom chapter 3.4

// inheritance without polymorphism
namespace test_3_4_1 {

struct C1 {
    int val;
    char ch1;
};

struct C2 : public C1 {
    char ch2;
};

struct C3 : public C2 {
    char ch3;
};

void test() {
    C1 c1;
    C2 c2;
    C3 c3;

    printf("sizeof c1: %d\n", sizeof c1);
    printf("sizeof c2: %d\n", sizeof c2);
    printf("sizeof c3: %d\n", sizeof c3);

    printf("memory layout of c3:\n");
    printf("&c3.val: %p\n", &c3.val);
    printf("&c3.ch1: %p\n", &c3.ch1);
    printf("&c3.ch2: %p\n", &c3.ch2);
    printf("&c3.ch3: %p\n", &c3.ch3);

    c2.ch2 = '2';
    c3.ch2 = '3';
    c3.ch3 = '4';

    printf("c3.ch2 = %c\n", c3.ch2);
    printf("c3.ch3 = %c\n", c3.ch3);

    C3* pc3 = static_cast<C3*>(&c2);
    printf("c2.ch3 = %c\n", pc3->ch3);
    c3 = *pc3;

    printf("c3.ch2 = %c\n", c3.ch2);
    printf("c3.ch3 = %c\n", c3.ch3);
}
} // namespace test_3_4_1

// add polymorphism
namespace test_3_4_2 {
struct A {
    int a, b;
    virtual void foo() {
        printf("A::foo()\n");
    }
};

struct B : public A {
    int c;
    void foo() {
        printf("B::foo()\n");
    }
};

void test() {
    A a;
    B b;

    a.foo();
    b.foo();

    A* pa = &b;
    pa->foo();
}
} // namespace test_3_4_2

// multiple inheritance
namespace test_3_4_3 {
struct A {
    int a1, a2;
    virtual void foo() {
        printf("A::foo()\n");
    }
};

struct B : public A {
    int b;
    void foo() {
        printf("B::foo()\n");
    }
};

struct C {
    int c;
    virtual void bar() {
        printf("C::bar()\n");
    }
};

struct D : public B, public C {
    int d;
    void foo() {
        printf("D::foo()\n");
    }

    void bar() {
        printf("D::bar()\n");
    }
};

void test() {
    A a;
    B b;
    C c;
    D d;

    a.foo();
    b.foo();
    c.bar();

    d.foo();
    d.bar();

    A* pa = &d;
    pa->foo();

    C* pc = &d;
    pc->bar();

}
} // namespace test_3_4_3

namespace test_3_4_4 {

struct A {
    int a1, a2;
    virtual void foo() {
        printf("A::foo()\n");
    }
};

struct B : public virtual A {
    int b;
    void foo() {
        printf("B::foo()\n");
    }
};

struct C : public virtual A {
    int c;
    void foo() {
        printf("C::foo()\n");
    }
};

struct D : public B, public C {
    int d;
    void foo() {
        printf("D::foo()\n");
    }
};

void test() {
    A a;
    B b;
    C c;
    D d;

    printf("sizeof A: %d\n", sizeof a);
    printf("sizeof B: %d\n", sizeof b);
    printf("sizeof C: %d\n", sizeof c);
    printf("sizeof D: %d\n", sizeof d);

    a.foo();
    b.foo();
    c.foo();

    d.foo();

    A* pa = &d;
    pa->foo();
}
} // namespace test_3_4_4


int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    printf("test_3_4_1 +++\n");
    test_3_4_1::test();
    printf("test_3_4_1 ---\n");

    printf("test_3_4_2 +++\n");
    test_3_4_2::test();
    printf("test_3_4_2 ---\n");

    printf("test_3_4_3 +++\n");
    test_3_4_3::test();
    printf("test_3_4_3 ---\n");

    printf("test_3_4_4 +++\n");
    test_3_4_4::test();
    printf("test_3_4_4 ---\n");

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
