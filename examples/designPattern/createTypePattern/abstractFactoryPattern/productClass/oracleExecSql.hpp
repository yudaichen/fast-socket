#ifndef FAST_SOCKET_ORACLE_EXEC_SQL_HPP
#define FAST_SOCKET_ORACLE_EXEC_SQL_HPP

#include "execSqlFactory.hpp"

class oracleExecSql : public execSqlFactory {

	void createExecSql() override
	{
		std::cout << "mysql create exec Sql" << std::endl;
	}

};

#endif //FAST_SOCKET_ORACLE_EXEC_SQL_HPP
