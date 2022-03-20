#ifndef FAST_SOCKET_DATABASE_POOLING_HPP
#define FAST_SOCKET_DATABASE_POOLING_HPP

/**
 * @brief 懒汉模式，只有执行了构建方法才会去执行
 */
class connect {

public:
	void log()
	{
		std::cout << "创建连接了" << std::endl;
	}
};
static connect *conn;

class databasePooling {

	databasePooling()
	{
		conn = nullptr;
	}

public:
	static connect *createConnect()
	{
		if (conn != nullptr)
		{
			conn = new connect();
		}
		return conn;
	}
};


#endif //FAST_SOCKET_DATABASE_POOLING_HPP
