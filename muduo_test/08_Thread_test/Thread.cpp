#include "Thread.h"
#include <iostream>
using namespace std;


Thread::Thread() : autoDelete_(false)
{
	cout<<"Thread ..."<<endl;
}

Thread::~Thread()
{
	cout<<"~Thread ..."<<endl;
}

void Thread::Start()
{
    // NOTICE: pthread_create的函数原型是：
    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    //                           void *(*start_routine) (void *), void *arg);
    // 其中的start_routine是要执行的函数，它的类型是void * (void *)
    //      而Thread::Run()不是普通的函数类型，它隐含了指向Thread对象的this指针
    //      Thread::ThreadRoutine是静态成员函数，它的类型是普通的函数类型：void * (void *)
	pthread_create(&threadId_, NULL, ThreadRoutine, this);
}

void Thread::Join()
{
	pthread_join(threadId_, NULL);
}

void* Thread::ThreadRoutine(void* arg)
{
    // 将传入的this指针转换为Thread指针
	Thread* thread = static_cast<Thread*>(arg);
    // 调用派生类实现的Run方法（多态）
	thread->Run();
    // 销毁线程对象
    // 先执行派生类的析构函数，再执行Thread抽象类的析构函数
	if (thread->autoDelete_)
		delete thread;
	return NULL;
}

void Thread::SetAutoDelete(bool autoDelete)
{
	autoDelete_ = autoDelete;
}
