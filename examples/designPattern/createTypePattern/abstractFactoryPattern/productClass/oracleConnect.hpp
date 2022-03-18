#ifndef FAST_SOCKET_ORACLE_CONNECT_HPP
#define FAST_SOCKET_ORACLE_CONNECT_HPP

#include "connectFactory.hpp"
#include <iostream>

class oracleConnect : public connectFactory {

	void createConnect() override
	{
		std::cout << "oracle create connect" << std::endl;
	}

};


#endif //FAST_SOCKET_ORACLE_CONNECT_HPP
