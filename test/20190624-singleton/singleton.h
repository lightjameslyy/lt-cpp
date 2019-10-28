#ifndef LT_SINGLETON_H_
#define LT_SINGLETON_H_

#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <stdlib.h> // atexit

namespace lt {

template<typename T>
class Singleton : boost::noncopyable {
  public:
    static T& instance() {
        pthread_once(&ponce_, &Singleton::init);
        return *value_;
    }

  private:
    Singleton();
    ~Singleton();

    static void init() {
        value_ = new T();
        // 在整个程序结束前执行
        ::atexit(destroy);
    }

    static void destroy() {
        // 在编译期间检查类型 T
        typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
        delete value_;
    }

  private:
    static pthread_once_t ponce_;
    static T*             value_;
};

template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = NULL;

}

#endif  // LT_SINGLETON_H_
