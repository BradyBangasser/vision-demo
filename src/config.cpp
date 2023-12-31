#include "config.hpp"
#include "constants.h"
#include "errors.hpp"
#include <wpi/raw_istream.h>

bool loadConfig(const char *cf, VisionConfig &vconfig) {
    std::error_code errorCode;

    // Attempts to open the config file
    wpi::raw_fd_istream is(cf, errorCode);

    if (errorCode) {
        ParseFatalError("I couldn't find the config file at {}, because {}", CONFIG_FILE, errorCode.message());
        return false;
    }

    wpi::json configFile;

    // Try to parse the config file
    try {
        configFile = wpi::json::parse(is);
    } catch (const wpi::json::parse_error &err) {
        ParseFatalError("I couldn't parse the config file at {}, because byte {}: ", CONFIG_FILE, err.byte, err.what());
        return false;
    }

    // Make sure config is valid
    if (!configFile.is_object()) {
        ParseFatalError("Config is invalid, must be Object not {}", configFile.type_name());
        return false;
    }

    // Get team number
    try {
        vconfig.team = configFile.at("team").get<unsigned int>();
    } catch (const wpi::json::exception &err) {
        ParseFatalError("Couldn't read team number: {}", err.what());
        return false;
    }

    // Network table mode
    if (configFile.count("ntmode")) {
        try {
            std::string str = configFile.at("ntmode").get<std::string>();
            if (wpi::equals_lower(str, "client")) {
                vconfig.enableNetworkTables = false;
            } else {
                vconfig.enableNetworkTables = true;
            }
        } catch (const wpi::json::exception &e) {
            ParseError("Could get Network Table mode: {}", e.what());
        }
    }

    // Load cameras
    try {
        for (auto &&camera : configFile.at("cameras")) {
            if (!loadCameraConfig(vconfig, camera)) {
                ParseFatalError("Failed to load camera");
                return false;
            } else {
                fmt::print("Loaded Camera {}\n", vconfig.cameras.size());
            }
        }
    } catch (const wpi::json::exception &err) {
        ParseFatalError("Couldn't load cameras: {}", err.what());
        return false;
    }

    return true;
} // loadConfig


bool loadCameraConfig(VisionConfig &vconfig, const wpi::json &config) {
    CameraConfig cconfig;

    // Get camera Name
    try {
        cconfig.name = config.at("name").get<std::string>();
        fmt::print("ccn: {}\n", cconfig.name);
    } catch (const wpi::json::exception &err) {
        ParseError("Failed to get camera name: {}", err.what());
        return false;
    }

    // Get camera path
    try {
        cconfig.path = config.at("path").get<std::string>();
        fmt::print("ccp: {}\n", cconfig.path);
    } catch (const wpi::json::exception &err) {
        ParseError("Failed to get camera path: {}", err.what());
        return false;
    }

    // stream props
    if (config.count("stream")) cconfig.streamConfig = config.at("stream");

    cconfig.config = config;

    vconfig.cameraConfigs.emplace_back(std::move(cconfig));

    return true;
}