#ifndef FAST_SOCKET_ORACLE_DESTROY_HPP
#define FAST_SOCKET_ORACLE_DESTROY_HPP

#include "destroyFactory.hpp"

class oracleDestroy : public destroyFactory {

	void createDestroy() override
	{
		std::cout << "oracle create destroy" << std::endl;
	}
};


#endif //FAST_SOCKET_ORACLE_DESTROY_HPP
