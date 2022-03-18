#ifndef FAST_SOCKET_DB_ABSTRACT_FACTORY_HPP
#define FAST_SOCKET_DB_ABSTRACT_FACTORY_HPP

#include <iostream>
#include <string>
#include <algorithm>

#include "connectFactory.hpp"
#include "destroyFactory.hpp"
#include "execSqlFactory.hpp"

/**
 * @brief 数据库连接抽象类
 */
class DBAbstractFactory {

public:
/**
 * @brief 连接数据库
 * @return 连接工厂
 */
virtual connectFactory *connect() = 0;

/**
 * @brief 销毁连接
 * @return 销毁工厂
 */
virtual destroyFactory *destroy() = 0;

/**
 * @brief 执行sql
 * @return 执行工厂
 */
virtual execSqlFactory *execSql() = 0;
};



#endif //FAST_SOCKET_DB_ABSTRACT_FACTORY_HPP
