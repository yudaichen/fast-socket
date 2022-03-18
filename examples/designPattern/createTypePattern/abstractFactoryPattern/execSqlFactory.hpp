#ifndef FAST_SOCKET_EXEC_SQL_FACTORY_HPP
#define FAST_SOCKET_EXEC_SQL_FACTORY_HPP

#include <iostream>

/**
 * @brief 数据库执行sql工厂
 */
class execSqlFactory {

public:
	/**
	 * @brief 数据库执行sql
	 */
	virtual void createExecSql() = 0;
};


#endif //FAST_SOCKET_EXEC_SQL_FACTORY_HPP
