/*******************************************************************************
    @file      main.cpp
    @brief     中介者模式---用一个中介对象来封装一系列的对象交互

	 多个对象之间的通信封装到一个类中单独处理

	 1、中国加入 WTO 之前是各个国家相互贸易，结构复杂，现在是各个国家通过 WTO 来互相贸易
	 2、机场调度系统
	 3、spring MVC 框架，其中C（控制器）就是 M（模型）和 V（视图）的中介者

    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include <iostream>
#include <list>
#include <utility>
#include<vector>
#include<string>
using namespace std;

class Visitor;
// 被访问元素
class Element
{
protected:
	std::string m_strName;
public:
	explicit Element(std::string str)
	{
		m_strName = std::move(str);
	}
	~Element() {};
	std::string getName()
	{
		return m_strName;
	}
	virtual void Accept(Visitor *visitor) = 0;
};

class ConcreteElementA: public Element
{
public:
	explicit ConcreteElementA(std::string str)
		: Element(std::move(str))
	{}
	void Accept(Visitor *visitor) override;
};

class ConcreteElementB: public Element
{
public:
	explicit ConcreteElementB(std::string str)
		: Element(std::move(str))
	{}
	void Accept(Visitor *visitor) override;
};

// 访问者
class Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA *p) = 0;
	virtual void VisitConcreteElementB(ConcreteElementB *p) = 0;
};

class ConcreteVisitorA: public Visitor
{
public:
	void VisitConcreteElementA(ConcreteElementA *p) override
	{
		std::cout << "ConcreteVisitorA 访问了" << p->getName() << std::endl;
	}
	void VisitConcreteElementB(ConcreteElementB *p) override
	{
		std::cout << "ConcreteVisitorA 访问了" << p->getName() << std::endl;
	}
};

class ConcreteVisitorB: public Visitor
{
public:
	void VisitConcreteElementA(ConcreteElementA *p) override
	{
		std::cout << "ConcreteVisitorB 访问了" << p->getName() << std::endl;
	}
	void VisitConcreteElementB(ConcreteElementB *p) override
	{
		std::cout << "ConcreteVisitorB 访问了" << p->getName() << std::endl;
	}
};

void ConcreteElementA::Accept(Visitor *visitor)
{
	visitor->VisitConcreteElementA(this);
}
void ConcreteElementB::Accept(Visitor *visitor)
{
	visitor->VisitConcreteElementB(this);
}
// 聚集类
class ObjectStructure
{
private:
	std::vector<Element *> m_vec;
public:
	~ObjectStructure()
	{
		for (auto & it : m_vec)
		{
			delete it;
		}
		m_vec.clear();
	}
	void add(Element *p)
	{
		m_vec.push_back(p);
	}
	void accept(Visitor *visitor)
	{
		for (auto it = m_vec.cbegin(); it != m_vec.cend(); it++)
		{
			(*it)->Accept(visitor);
		}
	}
};

int main()
{
	using namespace std;
	// 访问者模式
	ObjectStructure *p = new ObjectStructure();
	p->add(new ConcreteElementA("A"));
	p->add(new ConcreteElementB("B"));

	ConcreteVisitorA *pVisitorA = new ConcreteVisitorA();
	ConcreteVisitorB *pVisitorB = new ConcreteVisitorB();

	p->accept(pVisitorA);
	p->accept(pVisitorB);

	delete pVisitorA;
	delete pVisitorB;
	delete p;

	getchar();
	return 0;
}