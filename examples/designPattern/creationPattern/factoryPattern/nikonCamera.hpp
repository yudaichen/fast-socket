#ifndef FAST_SOCKET_NIKON_CAMERA_HPP
#define FAST_SOCKET_NIKON_CAMERA_HPP

#include "cameraFactory.hpp"

/**
 * @brief 尼康相机
 */
class nikonCamera : public cameraFactory {

	void createCamera() override
	{
		std::cout << "尼康相机被创建了" << std::endl;
	}
};


#endif //FAST_SOCKET_NIKON_CAMERA_HPP
