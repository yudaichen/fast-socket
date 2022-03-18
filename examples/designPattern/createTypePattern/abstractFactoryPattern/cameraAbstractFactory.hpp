
#ifndef FAST_SOCKET_CAMERA_HPP
#define FAST_SOCKET_CAMERA_HPP

#include <iostream>
#include <string>

/**
 * @brief 相机抽象工厂基类
 */
class cameraAbstractFactory {
public:
/**
 * @brief 构建相机
 */
	virtual void createCamera();
};


#endif //FAST_SOCKET_CAMERA_HPP
