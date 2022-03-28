#ifndef FAST_SOCKET_MYSQL_DESTROY_HPP
#define FAST_SOCKET_MYSQL_DESTROY_HPP

#include "destroyFactory.hpp"

class mysqlDestroy : public destroyFactory {

	void createDestroy() override
	{
		std::cout << "mysql create destroy" << std::endl;
	}
};


#endif //FAST_SOCKET_MYSQL_DESTROY_HPP
