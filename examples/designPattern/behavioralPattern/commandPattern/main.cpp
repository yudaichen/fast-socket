/*******************************************************************************
    @file      main.cpp
    @brief     命令模式

	命令模式，是将一个请求封装为一个对象，
    从而使我们可以用不同的请求对客户进行参数化、对请求排队或记录请求日志，以及支持可撤销的操作。
    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include <iostream>
#include <vector>
#include <list>
using namespace std;


// Receiver类，知道如何实施与执行一个与请求相关的操作：
class Receiver {
public:
	void Action() {
		cout << "Receiver" << endl;
	}
};

// Command类，用来声明执行操作的接口
class Command {
public:
	virtual void Execute() = 0;
	virtual void setReceiver(Receiver* r) = 0;
	virtual ~Command() = default;
};

// ConcreteCommand类，绑定一个Receiver，调用其相应操作以实现Execute：
class ConcreteCommand : public Command {
private:
	Receiver* receiver = nullptr;
public:
	void setReceiver(Receiver* r) override {
		receiver = r;
	}
	void Execute() override {
		receiver->Action();
	}
};

// 要求该命令执行这个请求：
class Invoker {
private:
	list<Command* > commands;
public:
	void setCommand(Command* c) {
		commands.push_back(c);
	}
	void Notify() {
		for (auto & command : commands) {
			command->Execute();
		}
	}
};

// 客户端实现代码：
int main() {
	Command* c = new ConcreteCommand();
	Receiver* r = new Receiver();
	c->setReceiver(r);

	Invoker i;
	i.setCommand(c);
	i.Notify();   // Receiver

	delete r;
	delete c;

	getchar();
	return 0;
}