/*******************************************************************************
    @file      main.cpp
    @brief    桥接模式 ----将两个独立变化的部分分离出来

	通过组合来实现，如此一来，操作系统不管如何变，客户的需求是不会变的（需求是：下载操作系统）

    使用场景: 对于两个独立变化的维度，使用桥接模式 在有多种可能会变化的情况下，用继承会造成类爆炸问题，扩展起来不灵活
    使用方式: 抽象类依赖实现类
    优点: 1、抽象和实现的分离。 2、优秀的扩展能力。 3、实现细节对客户透明
	缺点: 桥接模式的引入会增加系统的理解与设计难度，由于聚合关联关系建立在抽象层，要求开发者针对抽象进行设计与编程


    @details   ~
    @date      22.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

//操作系统
class OS {
public:
	virtual void InstallOS_Imp() = 0;
};

class WindowOS : public OS {
public:
	void InstallOS_Imp() override
	{ cout << "安装Window操作系统" << endl; }
};

class LinuxOS : public OS {
public:
	void InstallOS_Imp() override
	{ cout << "安装Linux操作系统" << endl; }
};

class UnixOS : public OS {
public:
	void InstallOS_Imp() override
	{ cout << "安装Unix操作系统" << endl; }
};

//计算机
class Computer {
public:
	virtual void InstallOS(OS *os) = 0;
};

//戴尔计算机
class DellComputer : public Computer {
public:
	void InstallOS(OS *os) override
	{ os->InstallOS_Imp(); }
};

//苹果计算机
class AppleComputer : public Computer {
public:
	void InstallOS(OS *os) override
	{ os->InstallOS_Imp(); }
};

//惠普计算机
class HPComputer : public Computer {
public:
	void InstallOS(OS *os) override
	{ os->InstallOS_Imp(); }
};

int main(int argc, char *argv[])
{
	OS *os1 = new WindowOS();
	OS *os2 = new LinuxOS();
	Computer *computer1 = new AppleComputer();
	computer1->InstallOS(os1);
	computer1->InstallOS(os2);
}