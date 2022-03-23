/*******************************************************************************
    @file      main.cpp
    @brief    装饰器模式 - 继承基类包装器，实现接口

	装饰器模式的优点：
	
	1、可以轻松对已存在的对象进行修改和包装，在被装饰者的前面或者后面添加自己的行为，而无需修改原对象。
	
	2、可以动态、不限量地进行装饰，可以更灵活地扩展功能。
	
	相对地，装饰器模式有很明显的缺点：
	
	1、会加入大量的小类，即使只添加一个功能，也要额外创建一个类，使得程序更复杂。
	
	2、增加代码复杂度，使用装饰器模式不但需要实例化组件，还要把组件包装到装饰者中

    @details   ~
    @date      23.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <list>
#include <utility>


using namespace std;


//定义一个原始的抽象类蛋糕，装饰器的功能是给蛋糕加上各种装饰，如奶油，巧克力，瓜子仁，花生米等
class Cake
{

public:
	virtual void showCake() = 0;
	
	virtual ~Cake() = default;;
	std::string name;
};

class ConcreteCake : public Cake
{
public:
	ConcreteCake() {
		name = "原始蛋糕";
	}
	
	void showCake() override { std::cout << name.c_str() << std::endl; };
	
	~ConcreteCake() override = default;;
};


class CakeDecorator : public Cake
{

protected:
	Cake *pCake;  //维护一个Cake对象的引用，为Cake对象添加装饰
public:
	void showCake() override = 0;
	
	CakeDecorator() {
		pCake = nullptr;
	}
	
	~CakeDecorator() override = default;
};

// 加奶油
class CakeDecoratorMilk : public CakeDecorator
{
public:
	explicit CakeDecoratorMilk(Cake *pCake) {
		this->pCake = pCake;
	}
	
	void showCake() override {
		this->name = pCake->name +  R"(add Milk)";
		std::cout << name.c_str() << std::endl;
	};
	
	~CakeDecoratorMilk() override = default;
};

// 加巧克力
class CakeDecoratorChocolates : public CakeDecorator
{
public:
	explicit CakeDecoratorChocolates(Cake *pCake) {
		this->pCake = pCake;
	}
	
	void showCake() override{
		this->name = pCake->name + R"(add Chocolates)" ;
		std::cout << name.c_str() << std::endl;
	}
	
	~CakeDecoratorChocolates() override = default;;
};


int main() {
	system("chcp 65001");
	
	ConcreteCake *pConCake = new ConcreteCake();
	pConCake->showCake();
	
	CakeDecoratorMilk *pDecMilk = new CakeDecoratorMilk(pConCake);
	pDecMilk->showCake();
	
	CakeDecoratorChocolates *pDecCho = new CakeDecoratorChocolates(pDecMilk);
	pDecCho->showCake();
	
	delete pConCake;
	delete pDecMilk;
	delete pDecCho;
	return 0;
}