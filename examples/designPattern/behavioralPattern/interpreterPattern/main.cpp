/*******************************************************************************
    @file      main.cpp
    @brief     解释器模式

 	构建语法树，定义终结符与非终结符

	解释器模式解决的问题是，如果一种特定类型的问题发生的频率足够高，
    那么可能就只得将该问题的各个示例表述为一个简单语言中的句子

    应用实例：编译器、运算表达式计算

    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include <iostream>
#include <list>
#include<vector>
#include<string>
using namespace std;

class Context
{
private:
	std::string m_strInput;
	std::string m_strOutput;
public:
	void setExpression(std::string str)
	{
		m_strInput = str;
	}
};

class Expression
{
public:
	virtual void Interpret(Context * context) = 0;
};

class TerminalExpression : public Expression
{
public:
	void Interpret(Context * context)
	{
		std::cout << "TerminalExpression!" << std::endl;
	}
};

class NonterminalExpression : public Expression
{
public:
	void Interpret(Context * context)
	{
		std::cout << "NonterminalExpression Expression!" << std::endl;
	}
};

int main()
{
	using namespace std;
	// 解释器模式
	Context * pContext = new Context();
	pContext->setExpression("Expression......");
	Expression * pNon = new NonterminalExpression();
	Expression * p = new TerminalExpression();
	// 根据Expression中的内容判断采用那种表达式解析
	pNon->Interpret(pContext);
	p->Interpret(pContext);
	delete p;
	delete pNon;
	delete pContext;

	getchar();
	return 0;
}