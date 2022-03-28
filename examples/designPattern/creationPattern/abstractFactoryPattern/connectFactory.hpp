#ifndef FAST_SOCKET_CONNECT_FACTORY_HPP
#define FAST_SOCKET_CONNECT_FACTORY_HPP

#include <iostream>

/**
 * @brief 数据库连接工厂
 */
class connectFactory {

public:
	/**
	 * @brief 数据库连接
	 */
	virtual void createConnect() = 0;
};


#endif //FAST_SOCKET_CONNECT_FACTORY_HPP
