#ifndef FAST_SOCKET_MYSQL_CONNECT_HPP
#define FAST_SOCKET_MYSQL_CONNECT_HPP

#include "connectFactory.hpp"

class mysqlConnect : public connectFactory {

	void createConnect() override
	{
		std::cout << "mysql create connect" << std::endl;
	}
};


#endif //FAST_SOCKET_MYSQL_CONNECT_HPP
