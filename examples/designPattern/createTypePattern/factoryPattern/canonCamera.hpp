#ifndef FAST_SOCKET_CANON_CAMERA_HPP
#define FAST_SOCKET_CANON_CAMERA_HPP
#include "cameraFactory.hpp"
/**
 * @brief 佳能相机
 */
class canonCamera : public cameraFactory{

	void createCamera() override{
		std::cout << "佳能相机被创建了"<< std::endl;
	}

};


#endif //FAST_SOCKET_CANON_CAMERA_HPP
