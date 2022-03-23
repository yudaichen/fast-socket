/*******************************************************************************
    @file      main.cpp
    @brief    组合模式

	1)    安全组合模式：将管理子元素的方法定义在Composite类中
	2)    透明组合模式：将管理子元素的方法定义在Component接口中，这样Leaf类就需要对这些方法空实现

	 组合模式包含如下角色：

	    • Component: 抽象构件

	    • Leaf: 叶子构件

	    • Composite: 容器构件

	    • Client: 客户类 ---- 调用Component

    @details   ~
    @date      23.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include<iostream>
#include<string>
#include<list>
#include <utility>
#include <vector>

using namespace std;

// 抽象构件
class ComponentPtr
{
protected:
	std::string m_strName;
public:
	explicit ComponentPtr(std::string str)
	{
		m_strName = std::move(str);
	}
	virtual void add(ComponentPtr* p) = 0;
	virtual void remove(ComponentPtr* p) = 0;
	virtual void display() = 0;
};

// 叶子节点
class LeafPtr : public ComponentPtr
{
public:
	explicit LeafPtr(std::string str)
		: ComponentPtr(std::move(str))
	{
	}
	void add(ComponentPtr* p) override
	{
		std::cout << "Leaf cannot add" << std::endl;
	}
	void remove(ComponentPtr* p) override
	{
		std::cout << "Leaf cannot remove" << std::endl;
	}
	void display() override
	{
		std::cout << m_strName << std::endl;
	}
};

class CompositePtr : public ComponentPtr
{
private:
	// Composite 容器组件
	std::vector<std::shared_ptr<ComponentPtr>> m_vec;
public:
	explicit CompositePtr(std::string str)
		: ComponentPtr(std::move(str))
	{
	};
	~CompositePtr()
	{
		if (!m_vec.empty())
		{
			m_vec.clear();
		}
	}
	void add(ComponentPtr* p) override
	{
		auto it = find_if(m_vec.begin(), m_vec.end(),
			[p](const std::shared_ptr<ComponentPtr>& ptr)
			{ return p == ptr.get(); });
		if (it == m_vec.end())
			m_vec.push_back(std::shared_ptr<ComponentPtr>(p));
	}
	void remove(ComponentPtr* p) override
	{
		auto it = find_if(m_vec.begin(), m_vec.end(),
			[p](const std::shared_ptr<ComponentPtr>& ptr)
			{ return p == ptr.get(); });
		if (it == m_vec.end())
			return;
		m_vec.erase(it);
	}
	void display() override
	{
		for (const auto & it : m_vec)
		{
			it->display();
		}
	}
};

int main()
{
	system("chcp 65001");
	using namespace std;
	// 组合模式
	CompositePtr* p = new CompositePtr("总部");
	p->add(new LeafPtr("总部财务部门"));
	p->add(new LeafPtr("总部人力资源部门"));

	CompositePtr* p1 = new CompositePtr("上海分部");
	p1->add(new LeafPtr("上海分部财务部门"));
	p1->add(new LeafPtr("上海分部人力资源部门"));
	p->add(p1);
	p->display();
	return 0;
}