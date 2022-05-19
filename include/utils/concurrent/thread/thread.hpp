﻿/**
 * @filename thread.hpp
 * @brief 线程类 ，支持Windows和Linux
 */

#ifndef _BASE_THREAD_HPP_
#define _BASE_THREAD_HPP_

#include <vector>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#else
#include <pthread.h>
#endif

namespace fast {

/// @brief 线程的工作函数
typedef std::function<void()> ThreadCallback;

/// @brief 线程类
class Thread
{
public:
	enum StateT { kInit, kStart, kJoined, kStop };

	explicit Thread(const ThreadCallback &cb)
		: _cb(cb)
		, _state(kInit)
#ifdef WIN32
	, _handle(NULL)
        , _threadId(0)
#endif
	{}

	~Thread()
	{
		join();
		_state = kStop;
	}

	/// @brief 启动线程
	/// @return 成功返回true，失败返回false
	bool start()
	{
		if (kInit != _state) {
			return false;
		}

		bool result = false;
#ifdef WIN32
		_handle = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadProc, (LPVOID)this, 0, &_threadId);
        result = (NULL != _handle);
#else
		int ret = pthread_create(&_thread, NULL, threadProc, (void *)this);
		result = (0 == ret);
#endif
		_state = kStart;
		return result;
	}

	/// @brief 结束线程
	/// @return 成功返回true，失败返回false
	bool stop()
	{
		if (kStop == _state || kInit == _state) {
			return true;
		}

		bool result = true;
#ifdef WIN32
		if(0 == ::TerminateThread(_handle, 0)) {
            result = false;
        }
#else
		if (0 != pthread_cancel(_thread)) {
			result = false;
		}
#endif
		if (result) {
			_state = kStop;
		}

		return result;
	}

	/// @brief 在当前线程中等待该线程结束
	/// @return 成功返回true，失败返回false
	bool join()
	{
		if (kStart != _state) {
			return false;
		}
		bool result = false;
#ifdef WIN32
		if (NULL != _handle) {
            DWORD ret = ::WaitForSingleObject(_handle, INFINITE);
            if (WAIT_OBJECT_0 == ret || WAIT_ABANDONED == ret) {
                result = true;
                _handle = NULL;
            }
        }
#else
		int ret = pthread_join(_thread, NULL);
		if (0 == ret) {
			result = true;
		}
#endif
		_state = kJoined;
		return result;
	}

#ifdef WIN32
	DWORD tid() const { return _threadId; }
    operator HANDLE() { return _handle; }
#else
	pthread_t tid() const { return _thread; }
#endif

private:
	//THEFOX_DISALLOW_EVIL_CONSTRUCTORS(Thread);

#ifdef WIN32
	static DWORD WINAPI threadProc(LPVOID param)
#else
	static void *threadProc(void *param)
#endif
	{
		Thread *pThis = reinterpret_cast<Thread *>(param);
		pThis->_cb();
		return 0;
	}

	ThreadCallback _cb;
	StateT _state;

#ifdef _WIN32
	HANDLE _handle;
    DWORD _threadId;
#else
	pthread_t _thread;
#endif
};

/// @breaf 线程组
class ThreadGroup
{
public:
	ThreadGroup()
	{}
	~ThreadGroup()
	{
		joinAll();
		for (size_t i = 0; i < _threads.size(); ++i) {
			delete _threads[i];
		}

		_threads.clear();
	}

	Thread *createThread(const ThreadCallback &threadfunc)
	{
		Thread *thread = new Thread(threadfunc);
		_threads.push_back(thread);
		return thread;
	}

	void addThread(Thread *thread)
	{
		_threads.push_back(thread);
	}

	void startAll()
	{
		for (size_t i = 0; i < _threads.size(); ++i) {
			_threads[i]->start();
		}
	}

	void joinAll()
	{
		for (size_t i = 0; i < _threads.size(); ++i) {
			_threads[i]->join();
		}
	}

	void stopAll()
	{
		for (size_t i = 0; i < _threads.size(); ++i) {
			_threads[i]->stop();
		}
	}

	size_t size() const { return _threads.size(); }

private:
	//THEFOX_DISALLOW_EVIL_CONSTRUCTORS(ThreadGroup);
	std::vector<Thread *> _threads;
};

}

#endif // _BASE_THREAD_HPP_