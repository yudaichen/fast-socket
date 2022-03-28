#ifndef FAST_SOCKET_MYSQL_FACTORY_HPP
#define FAST_SOCKET_MYSQL_FACTORY_HPP

#include "DBAbstractFactory.hpp"
#include "mysqlConnect.hpp"
#include "mysqlDestroy.hpp"
#include "mysqlExecSql.hpp"

class mysqlFactory : public DBAbstractFactory {
	/**
	 * @brief 连接数据库
	 * @return 连接工厂
	 */
	connectFactory *connect() override
	{
		return new mysqlConnect();
	}

	/**
	 * @brief 执行sql
	 * @return 执行工厂
	 */
	execSqlFactory *execSql() override{
		return new mysqlExecSql();
	}

	/**
	 * @brief 销毁连接
	 * @return 销毁工厂
	 */
	destroyFactory *destroy() override{
		return new mysqlDestroy();
	}

};


#endif //FAST_SOCKET_MYSQL_FACTORY_HPP
