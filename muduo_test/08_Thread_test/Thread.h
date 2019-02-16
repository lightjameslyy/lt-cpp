#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

// Thread类是一个抽象类
class Thread
{
public:
	Thread();
	virtual ~Thread();  // 知识点：纯虚析构函数

	void Start();
	void Join();

	void SetAutoDelete(bool autoDelete);

private:
	static void* ThreadRoutine(void* arg);
    // Run方法不能再主线程中直接调用，这样调用并不会在
    // 新创建的线程中执行任务
	virtual void Run() = 0;
	pthread_t threadId_;
	bool autoDelete_;
};

#endif // _THREAD_H_
