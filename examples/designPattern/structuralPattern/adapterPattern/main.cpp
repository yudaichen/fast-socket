/*******************************************************************************
    @file      main.cpp
    @brief    适配器模式可以将一个类的接口转换成客户端希望的另一个接口
    使用场景: 有动机地修改一个正常运行的系统的接口，这时应该考虑使用适配器模式
    使用方式: 继承或依赖（推荐）
    优点: 1、可以让任何两个没有关联的类一起运行。 2、提高了类的复用。 3、增加了类的透明度。 4、灵活性好。
	缺点:  过多地使用适配器，会让系统非常零乱，不易整体进行把握

	角色分析

	Target 目标角色，期望接口

	Adaptee 源角色，期望被转换的角色

	Adapter 适配器角色，核心，将元角色转换为目标角色，通过继承或者类关联的方式

    @details   ~
    @date      21.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Target {
protected:
	Target() = default;

public:
	virtual void request() = 0;

	virtual ~Target() = 0;
};

class ConcreteTarget : public Target {
public:

	void request() override
	{
		cout << "目标角色" << endl;
	}

};

class Adaptee {
public:

	void doSomething()
	{

		cout << "这是需要被转化的角色" << endl;
	}
};

class Adapter : public Target {
private:

	Adaptee *_adaptee;

public:

	void request() override
	{
		_adaptee->doSomething();
	}

	Adapter()
	{
		_adaptee = new Adaptee();
	}
};

int main(int argc, char *argv[])
{
	Adapter adapter;
	adapter.request();
}