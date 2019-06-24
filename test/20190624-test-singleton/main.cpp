#include <cstdio>
#include <iostream>

#include "singleton.h"

class A {
  public:
    A() {
        val_=1;
    }
    int value() {
        return val_;
    }
    ~A() {}
  private:
    int val_;
};

int main(int argc, char *argv[]) {
    A a = lt::Singleton<A>::instance();
    std::cout << a.value() << std::endl;
    A a1 = lt::Singleton<A>::instance();
    std::cout << a1.value() << std::endl;
    return 0;
}
