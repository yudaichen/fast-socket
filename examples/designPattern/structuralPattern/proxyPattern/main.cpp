/*******************************************************************************
    @file      main.cpp
    @brief    代理模式 ---  想在访问一个类时做一些控制

 使用场景：
	 1、远程代理。
	 2、虚拟代理。
	 3、Copy-on-Write 代理。
	 4、保护（Protect or Access）代理。
	 5、Cache代理。
	 6、防火墙（Firewall）代理。
	 7、同步化（Synchronization）代理。
	 8、智能引用（Smart Reference）代理。
    @details   ~
    @date      22.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include<iostream>
#include<string>
#include<list>
#include <utility>
#include<vector>
using namespace std;


class ProxyOpenImage
{
public:
	ProxyOpenImage() = default;

	~ProxyOpenImage() = default;

	void imRead(const string &path)
	{
		std::cout << "opencv go to read image :" << path << std::endl;
	}

};

class cvImage
{
public:
	explicit cvImage(const string &path)
	{
		if (proxyOpen == nullptr)
		{
			proxyOpen = new ProxyOpenImage();
		}
		imagePath = path;
	}
	~cvImage()
	{
		delete proxyOpen;
	}
	void imShow()
	{
		proxyOpen->imRead(imagePath);
	}

private:
	ProxyOpenImage *proxyOpen = nullptr;
	string imagePath;
};

int main()
{
	auto *image = new cvImage("proxy.jpg"); //代理
	image->imShow(); //需要时由代理负责打开
	delete image;
	return 0;
}