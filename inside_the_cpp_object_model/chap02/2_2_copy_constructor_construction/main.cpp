#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"

using namespace std;
using namespace chrono;


// reference: https://zh.cppreference.com/w/cpp/language/copy_constructor
namespace test_2_2_0 {
struct A {
    int n;
    A(int n = 1) : n(n) { }
    A(const A& a) : n(a.n) {
        printf("copy constructor A\n");
    } // 用户定义的复制构造函数
};

struct B : A {
    // 隐式默认构造函数 B::B()
    // 隐式复制构造函数 B::B(const B&)
};

struct C {
    int m;
    C(int m = 1): m(m) {}
    C(const C& b) = delete; // 阻止隐式生成复制构造函数
};

struct D : C {
    // 隐式默认构造函数 D::D()
    // 弃置的隐式复制构造函数 D::D(const D&) = delete
};

void test() {
    printf("test_2_2_0 begins...\n");
    A a1(7);
    A a2(a1); // 调用A的复制构造函数
    B b;
    B b2 = b; // 调用B的复制构造函数
    A a3 = b; // 转换到 A& 并调用复制构造函数
    volatile A va(10);
    // A a4 = va; // 编译错误，不能从volatile A转换为const A&

    C c;
    // C c2 = c; // 编译错误

    D d;
    // D d2 = d; // 基类或非静态成员无法复制
    printf("test_2_2_0 ends...\n");
}
} // namespace test_2_2_0

// reference: icom chapter 2.2
namespace test_2_2_1 {
struct Animal {
    Animal() {}
    virtual ~Animal() {}

    virtual void eat() {
        printf("Animal::eat\n");
    }
    virtual void sleep() {
        printf("Animal::sleep\n");
    }
  private:
    string name;
};

struct Bear: public Animal {
    void eat() {
        printf("Bear::eat\n");
    }
    void sleep() {
        printf("Bear::sleep\n");
    }
    virtual void dance() {
        printf("Bear::dance\n");
    }
};

struct Raccoon: public virtual Animal {
    Raccoon(): id(0) {}
    Raccoon(int id): id(id) {}
    void eat() {
        printf("Raccoon::eat\n");
    }
    void sleep() {
        printf("Raccoon::sleep\n");
    }
  private:
    int id;
};

struct RedPanda: public Raccoon {
    void eat() {
        printf("RedPanda::eat\n");
    }
    void sleep() {
        printf("RedPanda::sleep\n");
    }
};

void test() {
    // bitwise copy semantics
    Bear b;
    Bear yogi = b;
    yogi.eat();
    yogi.sleep();
    Animal franny = yogi;
    franny.eat();
    franny.sleep();

    // 多态
    Animal& an1 = yogi;
    an1.eat();
    an1.sleep();
    Animal* an2 = &yogi;
    an2->eat();
    an2->sleep();

    RedPanda rp;
    Raccoon rocky = rp;
    rocky.eat();
    rocky.sleep();
    Raccoon& rc = rp;
    rc.eat();
    rc.sleep();
}

} // namespace test_2_2_1


int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    test_2_2_0::test();
    test_2_2_1::test();

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
