/*******************************************************************************
    @file      main.cpp
    @brief     抽象工厂模式
    使用场景: 主要解决接口选择的问题
    使用方式: 在一个工厂里聚合多个同类产品
    优点: 当一个产品族中的多个对象被设计成一起工作时，它能保证客户端始终只使用同一个产品族中的对象
	缺点: 产品族扩展非常困难，会造成代码膨胀

    @details   ~
    @date      15.03.2022
    @copyright © Zhu zhao Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <algorithm>

#include "cameraAbstractFactory.hpp"
#include "canonCamera.hpp"
#include "nikonCamera.hpp"
#include "sonyCamera.hpp"

int main()
{
	const std::string cameraName = "佳能";

	cameraAbstractFactory *camera = nullptr;
	if (cameraName == "索尼") {
		camera = new sonyCamera();
    }else if (cameraName == "尼康") {
		camera = new nikonCamera();
    }else if (cameraName == "佳能") {
		camera =  new canonCamera();
    }

	if (camera != nullptr) {
		camera->createCamera();
    } else{
		std::cout << "没有找到对应的相机" << std::endl;
	}

	return 0;
}