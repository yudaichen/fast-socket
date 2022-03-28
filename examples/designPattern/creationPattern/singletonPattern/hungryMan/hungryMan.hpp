#ifndef FAST_SOCKET_DATABASE_POOLING_HPP
#define FAST_SOCKET_DATABASE_POOLING_HPP

#include <iostream>
#include <string>
#include <algorithm>

/**
 * @brief 懒汉模式、不管三七二十一、初始化就创建
 */
class connect {

public:
	void log()
	{
		std::cout << "创建连接了" << std::endl;
	}
};

class databasePooling {

private:
	static connect *conn;

public:
	static connect *createConnect()
	{
		return conn;
	}

	databasePooling()
	{
		conn = new class connect();
	}
};


#endif //FAST_SOCKET_DATABASE_POOLING_HPP
