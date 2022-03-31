#ifndef _BASE_MUTEX_HPP_
#define _BASE_MUTEX_HPP_

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

typedef CRITICAL_SECTION pthread_mutex_t;

#else
#include <pthread.h>
#endif
#include "utils/magic/common/nonCopyable.hpp"

namespace fast
{


/**
 * @brief windows下为临界区
 * 		  linux下为互斥锁
 */
class Mutex: public NonCopyable
{
public:
	Mutex()
		: _threadId(0)
	{
#ifdef WIN32
		InitializeCriticalSection(&_mutex);
#else
		pthread_mutex_init(&_mutex, NULL);
#endif
	}
	~Mutex()
	{
#ifdef WIN32
		DeleteCriticalSection(&_mutex);
#else
		pthread_mutex_destroy(&_mutex);
#endif
	}

	void lock()
	{
#ifdef WIN32
		EnterCriticalSection(&_mutex);
		_threadId = static_cast<uint32_t>(GetCurrentThreadId());
#else
		pthread_mutex_lock(&_mutex);
		_threadId = static_cast<uint32_t>(pthread_self());
#endif
	}

	void unlock()
	{
		_threadId = 0;
#ifdef WIN32
		LeaveCriticalSection(&_mutex);
#else
		pthread_mutex_unlock(&_mutex);
#endif
	}

	pthread_mutex_t *getMutex()
	{
		return &_mutex;
	}

private:
	uint32_t _threadId;             // 获取当前线程id
	pthread_mutex_t _mutex;         // 锁
};

/**
 * @brief 自动析构锁
 */
class MutexGuard: public NonCopyable
{
public:
	explicit MutexGuard(Mutex &mutex)
		: _mutex(mutex)
	{
		_mutex.lock();
	}
	~MutexGuard()
	{
		_mutex.unlock();
	}
private:
	Mutex &_mutex;                // 锁封装
};

#define MutexGuard(x) error "Missing MutexGuard object name"

}
#endif // _BASE_MUTEX_HPP_