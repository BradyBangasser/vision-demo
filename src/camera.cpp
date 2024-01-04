#include "camera.hpp"
#include "config.hpp"
#include <cscore.h>
#include <fmt/format.h>

Camera::Camera(const CameraConfig &config) {
    fmt::print("cn: {}\ncp: {}\n", config.name, config.path);
    this->usbCam = cs::UsbCamera{config.name, config.path};
    auto server = frc::CameraServer::StartAutomaticCapture(usbCam);

    this->usbCam.SetConfigJson(config.config);
    this->usbCam.SetConnectionStrategy(cs::VideoSource::kConnectionKeepOpen);

    // cs::CvSource cvSrc("cv", cs::VideoMode::kMJPEG, 640, 480, 30);
    // auto server1 = frc::CameraServer::StartAutomaticCapture(cvSrc);

    if (config.streamConfig.is_object()) server.SetConfigJson(config.streamConfig);
}