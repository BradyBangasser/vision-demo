#include "config.hpp"
#include "constants.h"
#include "errors.hpp"
#include <wpi/raw_istream.h>

bool loadConfig(VisionConfig &vconfig) {
    std::error_code errorCode;

    // Attempts to open the config file
    wpi::raw_fd_istream is(CONFIG_FILE, errorCode);

    if (errorCode) {
        ParseFatalError("I couldn't find the config file at {}, because {}", CONFIG_FILE, errorCode.message());
        return false;
    }

    wpi::json configFile;

    // Try to parse the config file
    try {
        configFile = wpi::json::parse(is);
    } catch (const wpi::json::parse_error &e) {
        ParseFatalError("I couldn't parse the config file at {}, because byte {}: ", CONFIG_FILE, e.byte, e.what());
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
    } catch (const wpi::json::exception &e) {
        ParseFatalError("Couldn't read team number: {}", e.what());
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
            }
        }
    } catch (const wpi::json::exception &e) {
        ParseFatalError("Couldn't load cameras: {}", e.what());
        return false;
    }
} // loadConfig


bool loadCameraConfig(VisionConfig &vconfig, const wpi::json &config) {
    CameraConfig cconfig;

    try {

    } catch (const wpi::json::exception &e) {
        
    }
}