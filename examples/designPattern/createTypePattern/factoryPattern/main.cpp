/*******************************************************************************
    @file      main.cpp
    @brief     工厂模式
    使用场景: 主要解决接口选择的问题
    使用方式: 创建过程在其子类执行
    优点: 屏蔽产品的具体实现，调用者只关心产品的接口
	缺点: 每次增加一个产品时，都需要增加一个具体类和对象实现工厂，会造成代码膨胀

    @details   ~
    @date      15.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <algorithm>

#include "cameraFactory.hpp"
#include "canonCamera.hpp"
#include "nikonCamera.hpp"
#include "sonyCamera.hpp"

int main()
{
	const std::string cameraName = "佳能";

	cameraFactory *camera = nullptr;
	if (cameraName == "索尼")
	{
		camera = new sonyCamera();
	} else if (cameraName == "尼康")
	{
		camera = new nikonCamera();
	} else if (cameraName == "佳能")
	{
		camera = new canonCamera();
	}

	std::cout << cameraName << std::endl;

	if (camera != nullptr)
	{
		camera->createCamera();
	} else
	{
		std::cout << "没有找到对应的相机" << std::endl;
	}

	return 0;
}