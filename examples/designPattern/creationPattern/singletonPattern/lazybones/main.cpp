/*******************************************************************************
    @file      main.cpp
    @brief     单例模式
    使用场景: 一个全局使用的类频繁地创建与销毁
    使用方式: 判断系统是否已经有这个单例，如果有则返回，如果没有则创建
    优点: 在内存里只有一个实例，减少了内存的开销，尤其是频繁的创建和销毁实例
	缺点: 没有接口，不能继承，与单一职责原则冲突

    @details   ~
    @date      15.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>

#include "lazybones.hpp"
#include "threadSafeLazybones.hpp"

int main()
{
	// 单线程模式懒汉
	connect *conn = databasePooling::createConnect();

	conn->log();

	std::vector<std::thread> threads;
	for (int count = 0; count < 50; ++count)
	{

		threads.emplace_back([]() {

			// 线程安全模式下懒汉
			safeConnect *safe = threadSafeLazybones::createConnect();
			safe->log();
		});

	}
	// 开始执行线程
	for (auto &thread: threads)
	{
		thread.join();
	}


	return 0;
}
