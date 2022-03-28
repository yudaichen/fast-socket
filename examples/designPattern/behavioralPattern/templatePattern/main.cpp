/*******************************************************************************
    @file      main.cpp
    @brief    模板模式 ----在抽象类实现，其他步骤在子类实现


	 spring 中对 Hibernate 的支持，将一些已经定好的方法封装起来，
	 比如开启事务、获取 Session、关闭 Session 等，
	 程序员不重复写那些已经规范好的代码，直接丢一个实体就可以保存

    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include<iostream>
#include<list>

using namespace std;

//简历
class Resume
{
protected: //保护成员
	virtual void SetPersonalInfo()
	{}
	virtual void SetEducation()
	{}
	virtual void SetWorkExp()
	{}
public:
	void FillResume()
	{
		SetPersonalInfo();
		SetEducation();
		SetWorkExp();
	}
};

class ResumeA: public Resume
{
protected:
	void SetPersonalInfo() override
	{ cout << "A's PersonalInfo" << endl; }
	void SetEducation() override
	{ cout << "A's Education" << endl; }
	void SetWorkExp() override
	{ cout << "A's Work Experience" << endl; }
};

class ResumeB: public Resume
{
protected:
	void SetPersonalInfo() override
	{ cout << "B's PersonalInfo" << endl; }
	void SetEducation() override
	{ cout << "B's Education" << endl; }
	void SetWorkExp() override
	{ cout << "B's Work Experience" << endl; }
};

int main()
{
	Resume *r1;
	r1 = new ResumeA();
	r1->FillResume();
	delete r1;
	r1 = new ResumeB();
	r1->FillResume();
	delete r1;
	r1 = nullptr;
	getchar();
	return 0;
}