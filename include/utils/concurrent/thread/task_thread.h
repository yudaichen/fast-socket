/**
 * @file task_thread.h
 * @brief 任务线程对象
 * @version 1.0.0
 * @date 2018-01-02
 */
#pragma once

#include <memory>
#include <thread>
#include <atomic>
#include <functional>
#include "nonCopyable.hpp"

namespace fast
{


class task_thread: public NonCopyable
{
public:
	explicit task_thread(const std::function<void()> &func);
	~task_thread();

	void stop();
	std::thread::id get_thread_id();

private:
	void task_func();

private:
	std::function<void()> func_;
	std::shared_ptr<std::thread> thread_;
	std::atomic<bool> active_{false};
};

}