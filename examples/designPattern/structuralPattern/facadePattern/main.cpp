/*******************************************************************************
    @file      main.cpp
    @brief    外观模式 - 客户看到这个方法知道干什么就行，不需要知道内部实现
    
    1、假设"gcc 编译"一个程序需要经过四个步骤：词法分析、语法分析、中间代码生成、机器码生成
   
	2、可以定义一个高层接口
 
	3、在接口中定义一个run()方法
	
	4、客户端调用run
    @details   ~
    @date      23.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include <iostream>
#include <list>

using namespace std;

class Scanner
{
public:
	void Scan() { cout << "词法分析" << endl; }
};

class Parser
{
public:
	void Parse() { cout << "语法分析" << endl; }
};

class GenMidCode
{
public:
	void GenCode() { cout << "产生中间代码" << endl; }
};

class GenMachineCode
{
public:
	void GenCode() { cout << "产生机器码" << endl; }
};

//高层接口
class Compiler
{
public:
	void Run() {
		Scanner scanner;
		Parser parser;
		GenMidCode genMidCode;
		GenMachineCode genMacCode;
		scanner.Scan();
		parser.Parse();
		genMidCode.GenCode();
		genMacCode.GenCode();
	}
};

int main() {
	Compiler compiler;
	compiler.Run();
	
	getchar();
	return 0;
}