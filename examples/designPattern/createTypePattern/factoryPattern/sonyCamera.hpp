//
// Created by 余代宸 -Yu DaiChen on 2022/3/18
// QQ-E-MAIL:250074249@qq.com
//

#ifndef FAST_SOCKET_SONY_CAMERA_HPP
#define FAST_SOCKET_SONY_CAMERA_HPP

#include "cameraFactory.hpp"

/**
 * @brief 索尼相机
 */
class sonyCamera : public cameraFactory {

	void createCamera() override
	{
		std::cout << "索尼相机被创建了" << std::endl;
	}
};


#endif //FAST_SOCKET_SONY_CAMERA_HPP
