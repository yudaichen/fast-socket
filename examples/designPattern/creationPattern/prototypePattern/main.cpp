/*******************************************************************************
    @file      main.cpp
    @brief    是用于创建重复的对象，同时又能保证性能
    使用场景: 1、细胞分裂。 2、类似于 JAVA 中的 Object clone() 方法
    使用方式: 利用已有的一个原型对象，快速地生成和原型对象一样的实例
    优点: 1、性能提高。 2、逃避构造函数的约束。
	缺点:  1、产品必须有共同点，范围有限制。 2、如内部变化复杂，会有很多的建造类。

 	类似于cv::Mat
 	cv::Mat inputMat,outMat;
 	outMat = inputMat;//只是指向了outMat
 	outMat = inputMat.clone(); //拷贝了一份出来了

 	如：Parent *Parent = new Parent();

 	Daughter *daughter =Parent;
 	Son *Son = Parent;
 	delete Parent;//如果这里我们释放parent的内存，新成员son和c都是从daughter拷贝过来，就无法实现，因为内存已经被释放
 	daughter->getRole();
	daughter->getRole();
	Son->getRole();

    @details   ~
    @date      21.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Parent {
public:
	string role;

public:
	explicit Parent(const char *sRole)
	{ role = sRole; }

	Parent() = default;

	~Parent() = default;

	void getRole()
	{
		cout << "角色:" << role << endl;
	}

	virtual Parent *clone() = 0;    //定义一个纯虚函数，纯虚函数就是虚基类，这里就是一个接口，接口不能实例化一个对象，它的作用就是被子类继承，

};

class Daughter : public Parent {
public:
	explicit Daughter(const char *sRole) : Parent(sRole)
	{}

	Daughter() = default;

	~Daughter() = default;

	Parent *clone() override
	{
		Daughter *p = new Daughter();    //这里就是实现了上图中的return copy of self
		*p = *this;
		return p;
		//return new Daughter(*this);    //或者用这一句话替代上面三句
	}
};

class Son : public Parent {
public:
	explicit Son(const char *sRole) : Parent(sRole)
	{}

	Son() = default;

	~Son() = default;

	Parent *clone() override
	{
		Son *p = new Son();//这里就是实现了上图中的return copy of self
		*p = *this;
		return p;
		// return new Son(*this);    //或者用这一句话替代上面三句
	}
};

int main(int argc, char *argv[])
{
	Son *son = new Son("儿子");
	son->getRole();
	Daughter *daughter = new Daughter("女儿");
	daughter->getRole();

	Parent *mon = daughter->clone();
	mon->getRole();
	Parent *daddy = son->clone();
	daddy->getRole();

	delete son;
	delete daughter;
	mon->role = "母亲";
	mon->getRole();
	daddy->role = "父亲";
	daddy->getRole();
	return 0;
}