#ifndef FAST_SOCKET_ORACLE_FACTORY_HPP
#define FAST_SOCKET_ORACLE_FACTORY_HPP

#include "DBAbstractFactory.hpp"

#include "oracleConnect.hpp"
#include "oracleDestroy.hpp"
#include "oracleExecSql.hpp"

class oracleFactory : public DBAbstractFactory {

	/**
	 * @brief 连接数据库
	 * @return 连接工厂
	 */
	connectFactory *connect() override
	{
		return new oracleConnect();
	}

	/**
	 * @brief 执行sql
	 * @return 执行工厂
	 */
	execSqlFactory *execSql() override
	{
		return new oracleExecSql();
	}

	/**
	 * @brief 销毁连接
	 * @return 销毁工厂
	 */
	destroyFactory *destroy() override
	{
		return new oracleDestroy();
	}

};


#endif //FAST_SOCKET_ORACLE_FACTORY_HPP
