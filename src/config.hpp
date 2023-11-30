#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <vector>
#include <string>
#include <wpi/json.h>
#include <CameraServer.h>

// TODO, make this better
struct CameraConfig {
    std::string name;
    std::string path;
    wpi::json config;
    wpi::json streamConfig;
};

struct VisionConfig {
    unsigned int team;
    bool enableNetworkTables;
    std::vector<CameraConfig> cameraConfigs;
    std::vector<cs::VideoSource> cameras;
};

// TODO make this better
bool loadCameraConfig(const VisionConfig &vconfig, const wpi::json &config);
bool loadConfig(const VisionConfig &vconfig);

#endif