/*******************************************************************************
    @file      main.cpp
    @brief    空对象模式模式

	需要在无法创建具体实例或数据不可用的时候提供默认行为，
	 则需要用空对象模式，而不是仅仅返回一个NULL值

 例如java 的获取map值的方法：

	default V getOrDefault(Object key, V defaultValue) {
	        V v;
	        return (((v = get(key)) != null) || containsKey(key)) ? v : defaultValue;
	 }
    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/


#include<iostream>
#include<string>

using namespace std;

//创建一个抽象类AbstractCustomer。
class AbstractCustomer
{
public:
	AbstractCustomer() = default;
	virtual ~AbstractCustomer() = default;
	virtual bool isnull()=0;
	virtual string getName() = 0;

protected:
	string name;
};

//创建扩展了抽象类AbstractCustomer的实体类RealCustomer。
class RealCustomer :AbstractCustomer
{
public:
	explicit RealCustomer(string sName) { name = sName; };
	~RealCustomer() override = default;
	bool isnull() override { return false; };
	string getName() override { return name; };
};

//创建扩展了抽象类AbstractCustomer的空类NullCustomer。
class NullCustomer :AbstractCustomer
{
public:
	NullCustomer() = default;
	~NullCustomer() override = default;
	bool isnull() override { return true; };
	string getName() override { return "Not Available in coustomer database"; };
};

//创建CustomerFactory类，用来获取实体类或空类的实例
class CustomerFactory
{
public:
	CustomerFactory() = default;
	~CustomerFactory() = default;
	static string name[3];
	static AbstractCustomer* getCustomer(string tname);
};

string CustomerFactory::name[3] = { "Rob","Joe","Julie" };

AbstractCustomer* CustomerFactory::getCustomer(string tname)
{
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (name[i] == tname)
		{
			return (AbstractCustomer*)new RealCustomer(tname);
		}
	}
	return (AbstractCustomer*)new NullCustomer();
}

int main()
{
	AbstractCustomer *c1 = CustomerFactory::getCustomer("Rob");
	AbstractCustomer *c2 = CustomerFactory::getCustomer("Mickel");
	AbstractCustomer *c3 = CustomerFactory::getCustomer("Joe");
	AbstractCustomer *c4 = CustomerFactory::getCustomer("Julie");

	cout << "Rob: " << c1->getName() << endl;
	cout << "Mickel: " << c2->getName() << endl;
	cout << "Joe: " << c3->getName() << endl;
	cout << "Juile: " << c4->getName() << endl;

	delete c1;
	c1 = NULL;

	delete c2;
	c2 = NULL;

	delete c3;
	c3 = NULL;

	delete c4;
	c4 = NULL;

	return 0;
}