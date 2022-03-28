/*******************************************************************************
    @file      main.cpp
    @brief     观察者模式 ---- 一个对象（目标对象）的状态发生改变，所有的依赖对象（观察者对象）都将得到通知，进行广播通知

	 依赖(Dependents)
	 发布-订阅(Publish-Subscribe to)

	Subject: 目标
	ConcreteSubject: 具体目标
	Observer: 观察者
	ConcreteObserver: 具体观察者


 使用注意：
	1、避免循环引用。
 	2、如果顺序执行，某一观察者错误会导致系统卡壳，一般采用异步方式。

    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include <iostream>
#include <string>z
#include <list>
#include <utility>


using namespace std;

//观察者 基类
class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = default;
	virtual void Update()
	{}
};

//博客 基类
class Blog
{
public:
	Blog() = default;
	virtual ~Blog() = default;
	void Attach(Observer *observer)
	{ m_observers.push_back(observer); }     //添加观察者
	void Remove(Observer *observer)
	{ m_observers.remove(observer); }        //移除观察者
	void Notify() //通知观察者
	{
		auto iter = m_observers.begin();
		for (; iter != m_observers.end(); iter++)
			(*iter)->Update();
	}
	virtual void SetStatus(string s)
	{ m_status = std::move(s); } //设置状态
	virtual string GetStatus()
	{ return m_status; }    //获得状态
private:
	list<Observer *> m_observers; //观察者链表
protected:
	string m_status; //状态
};

//具体博客类
class BlogCSDN: public Blog
{
private:
	string m_name; //博主名称
public:
	explicit BlogCSDN(string name)
		: m_name(std::move(name))
	{}
	~BlogCSDN() override = default;
	void SetStatus(string s) override
	{ m_status = "CSDN通知 : " + m_name + s; } //具体设置状态信息
	string GetStatus() override
	{ return m_status; }
};

//具体观察者
class ObserverBlog: public Observer
{
private:
	string m_name;  //观察者名称
	Blog *m_blog;   //观察的博客，当然以链表形式更好，就可以观察多个博客
public:
	ObserverBlog(string name, Blog *blog)
		: m_name(std::move(name)), m_blog(blog)
	{}
	~ObserverBlog() override = default;
	void Update() override  //获得更新状态
	{
		string status = m_blog->GetStatus();
		cout << m_name << "-------" << status << endl;
	}
};

//测试案例
int main()
{
	Blog *blog = new BlogCSDN("hhhhhhh");
	Observer *observer1 = new ObserverBlog("tutupig", blog);
	blog->Attach(observer1);
	blog->SetStatus("发表设计模式C++——观察者模式");
	blog->Notify();
	delete blog;
	delete observer1;
	getchar();
	return 0;
}