#ifndef FAST_SOCKET_THREAD_SAFE_LAZYBONES_HPP
#define FAST_SOCKET_THREAD_SAFE_LAZYBONES_HPP

#include <mutex>

static int i;


class safeConnect {
public:
	void log()
	{
		std::cout << "创建连接了" << i << std::endl;
	}
};

static safeConnect *safeConn;

static std::mutex mutex;

/**
 * @brief 线程安全的懒汉
 */
class threadSafeLazybones {

	threadSafeLazybones()
	{
		safeConn = nullptr;
		i = 0;
	}


public:
	static safeConnect *createConnect()
	{
		// 括号生命周期后 自动结构解锁
		std::lock_guard<std::mutex> lock(mutex);
		if (safeConn != nullptr)
		{
			safeConn = new safeConnect();
			i++;
		}
		return safeConn;
	}
};


#endif //FAST_SOCKET_THREAD_SAFE_LAZYBONES_HPP
