#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cscore.h>
#include "config.hpp"

class Camera : public cs::UsbCamera {
    private: 
        cs::UsbCamera usbCam;
    public:
        Camera(const CameraConfig &config);
};

#endif