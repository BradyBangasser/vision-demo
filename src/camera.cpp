#include "camera.hpp"
#include "config.hpp"
#include <cscore.h>
#include <fmt/format.h>

Camera::Camera(const CameraConfig &config) {
    fmt::print("cn: {}\ncp: {}\n", config.name, config.path);
    this->usbCam = cs::UsbCamera{config.name, config.path};
    auto server = frc::CameraServer::StartAutomaticCapture(this->usbCam);

    this->usbCam.SetConfigJson(config.config);
    this->usbCam.SetConnectionStrategy(cs::VideoSource::kConnectionKeepOpen);

    if (config.streamConfig.is_object()) server.SetConfigJson(config.streamConfig);
}