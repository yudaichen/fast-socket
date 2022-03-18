/*******************************************************************************
    @file      main.cpp
    @brief     抽象工厂模式
    使用场景: 主要解决接口选择的问题
    使用方式: 在一个工厂里聚合多个同类产品 如:mysql就是产品族 内部连接、sql执行、销毁链接就是产品等级
    优点: 当一个产品族中的多个对象被设计成一起工作时，它能保证客户端始终只使用同一个产品族中的对象
	缺点: 产品族扩展非常困难，会造成代码膨胀

    @details   ~
    @date      18.03.2022
    @copyright © Zhu zhao Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include "DBAbstractFactory.hpp"
#include "mysqlFactory.hpp"
#include "oracleFactory.hpp"

int main()
{
	std::string useDatabaseName = "sqlServer";
	DBAbstractFactory *dbAbstractFactory = nullptr;
	if (useDatabaseName == "oracle")
	{
		dbAbstractFactory = new oracleFactory();
	} else if (useDatabaseName == "mysql")
	{
		dbAbstractFactory = new mysqlFactory();
	}
	if (dbAbstractFactory != nullptr)
	{
		dbAbstractFactory->connect()->createConnect();
		dbAbstractFactory->execSql()->createExecSql();
		dbAbstractFactory->destroy()->createDestroy();
	} else
	{
		std::cout << "没有找到[" << useDatabaseName << "]驱动";
	}

	return 0;
}