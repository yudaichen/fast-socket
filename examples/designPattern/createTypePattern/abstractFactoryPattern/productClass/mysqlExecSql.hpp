#ifndef FAST_SOCKET_MYSQL_EXEC_SQL_HPP
#define FAST_SOCKET_MYSQL_EXEC_SQL_HPP

#include "execSqlFactory.hpp"

class mysqlExecSql : public execSqlFactory {

	void createExecSql() override
	{
		std::cout << "mysql create exec Sql" << std::endl;
	}

};


#endif //FAST_SOCKET_MYSQL_EXEC_SQL_HPP
