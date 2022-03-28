/*******************************************************************************
    @file      main.cpp
    @brief    访问者模式 ---- 作用于某对象结构中的各元素的操


    在数据基础类里面有一个方法接受访问者，将自身引用传入访问者


 数据结构上 与 操作 解开耦合

 访问者模式
	定义：您在朋友家做客，您是访问者，
	步骤1：朋友接受您的访问，
	步骤2：您通过朋友的描述，
	步骤3：然后对朋友的描述做出一个判断，


    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include <iostream>
#include <list>
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
	Element(std::string str)
	{
		m_strName = str;
	}
	std::string getName()
	{
		return m_strName;
	}
	virtual void Accept(Visitor * visitor) = 0;
};

class ConcreteElementA : public Element
{
public:
	ConcreteElementA(std::string str) : Element(str) {}
	void Accept(Visitor * visitor);
};

class ConcreteElementB : public Element
{
public:
	ConcreteElementB(std::string str) : Element(str) {}
	void Accept(Visitor * visitor);
};

// 访问者
class Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA * p) = 0;
	virtual void VisitConcreteElementB(ConcreteElementB * p) = 0;
};

class ConcreteVisitorA : public Visitor
{
public:
	void VisitConcreteElementA(ConcreteElementA * p)
	{
		std::cout << "ConcreteVisitorA 访问了" << p->getName() << std::endl;
	}
	void VisitConcreteElementB(ConcreteElementB * p)
	{
		std::cout << "ConcreteVisitorA 访问了" << p->getName() << std::endl;
	}
};

class ConcreteVisitorB : public Visitor
{
public:
	void VisitConcreteElementA(ConcreteElementA * p)
	{
		std::cout << "ConcreteVisitorB 访问了" << p->getName() << std::endl;
	}
	void VisitConcreteElementB(ConcreteElementB * p)
	{
		std::cout << "ConcreteVisitorB 访问了" << p->getName() << std::endl;
	}
};

void ConcreteElementA::Accept(Visitor * visitor)
{
	visitor->VisitConcreteElementA(this);
}
void ConcreteElementB::Accept(Visitor * visitor)
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
		for (auto it = m_vec.begin(); it != m_vec.end(); it++)
		{
			delete *it;
		}
		m_vec.clear();
	}
	void add(Element * p)
	{
		m_vec.push_back(p);
	}
	void accept(Visitor * visitor)
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

	// 元素集合
	ObjectStructure * p = new ObjectStructure();
	p->add(new ConcreteElementA("A"));
	p->add(new ConcreteElementB("B"));

	// 访问者
	ConcreteVisitorA * pVisitorA = new ConcreteVisitorA();
	ConcreteVisitorB * pVisitorB = new ConcreteVisitorB();

	p->accept(pVisitorA);
	p->accept(pVisitorB);

	delete pVisitorA;
	delete pVisitorB;
	delete p;

	getchar();
	return 0;
}