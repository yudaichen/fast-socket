/*******************************************************************************
    @file      main.cpp
    @brief     责任链模式

	职责链上的处理者负责处理请求，
	客户只需要将请求发送到职责链上即可，
	无须关心请求的处理细节和请求的传递，
	所以职责链将请求的发送者和请求的处理者解耦了。

	Apache Tomcat 对 Encoding 的处理
	Struts2 的拦截器，
	jsp servlet 的 Filter

    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Handler
{
public:
	Handler() { m_pNextHandler = nullptr; }
	virtual ~Handler() = default;;

	//设置下一个处理者
	void SetNextHandler(Handler *successor) { m_pNextHandler = successor; }

	//处理请求
	virtual void HandleRequest(int days)
	{

	};
protected:
	Handler *m_pNextHandler;
};

class Director : public Handler{
public:
	//处理请求
	void HandleRequest(int days) override
	{
		if (days <= 1)
		{
			cout << "我是主管，有权批准一天假，同意了！" << endl;
		}
		else
		{
			m_pNextHandler->HandleRequest(days);
		}
	}
};

class Manager :public Handler
{
public:
	//处理请求
	void HandleRequest(int days) override
	{
		if (days <= 3)
		{
			cout << "我是经理，有权批准三以下的假，同意了！" << endl;
		}
		else
		{
			m_pNextHandler->HandleRequest(days);
		}
	}
};

class Boss :public Handler
{
public:
	//处理请求
	void HandleRequest(int days) override
	{
		if (days <= 7)
		{
			cout << "我是老板，最多让你请7天假，同意了！" << endl;
		}
		else
		{
			cout << "你请的假事假太长了，不同意！" << endl;
		}
	}
};



//场景
int main()
{
	Handler *director = new Director;
	Handler *manager = new Manager;
	Handler *boss = new Boss;

	//设置责任链
	director->SetNextHandler(manager);
	manager->SetNextHandler(boss);

	director->HandleRequest(1);
	director->HandleRequest(2);
	director->HandleRequest(5);
	director->HandleRequest(8);
	return 0;
}