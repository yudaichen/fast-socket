﻿/*
* @filename read_write_lock.h
* @brief 读写锁
*/

#ifndef _BASE_READ_WRITE_LOCK_H_
#define _BASE_READ_WRITE_LOCK_H_

#include <base/common.h>
#include <base/atomic_integer.h>
#include <base/mutex.h>

namespace thefox {

class ReadWriteLock
{
public:
	ReadWriteLock()
		: _reads(0)
	{}

	~ReadWriteLock()
	{}

	void readLock()
	{
		_enterLock.lock();
		atomicInc(&_reads);
		_enterLock.unlock();
	}

	void readUnlock()
	{
		atomicDec(&_reads);
	}

	void writeLock()
	{
		_enterLock.lock();
		while (_reads > 0) {
			Sleep(0);
		}
	}

	void writeUnlock()
	{
		_enterLock.unlock();
	}

private:
	THEFOX_DISALLOW_EVIL_CONSTRUCTORS(ReadWriteLock);
	volatile uint32_t _reads;
	MutexLock _enterLock;
};

class ReadLockGuard
{
public:
	ReadLockGuard(ReadWriteLock &lock)
		: _lock(lock)
	{
		_lock.readLock();
	}
	~ReadLockGuard()
	{
		_lock.readUnlock();
	}
private:
	THEFOX_DISALLOW_EVIL_CONSTRUCTORS(ReadLockGuard);
	ReadWriteLock &_lock;
};

class WriteLockGuard
{
public:
	WriteLockGuard(ReadWriteLock &lock)
		: _lock(lock)
	{
		_lock.writeLock();
	}
	~WriteLockGuard()
	{
		_lock.writeUnlock();
	}
private:
	THEFOX_DISALLOW_EVIL_CONSTRUCTORS(WriteLockGuard);
	ReadWriteLock &_lock;
};

#define ReadLockGuard(x) error "Missing guard object name"
#define WriteLockGuard(x) error "Missing guard object name"
}

#endif // _BASE_READ_WRITE_LOCK_H_