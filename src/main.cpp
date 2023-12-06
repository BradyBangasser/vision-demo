#include "cameraserver/CameraServer.h"
#include "config.hpp"
#include "constants.h"
#include "camera.hpp"
#include "pipeline.hpp"

#include <fmt/format.h>
#include <thread>
#include <vision/VisionRunner.h>

int main(int argc, char *argv[]) {
    const char *configFile = (argc > 2) ? argv[2] : CONFIG_FILE;
    VisionConfig config;

    fmt::print("Loading configuration...\n");
    loadConfig(configFile, config);
    fmt::print("Loaded configuration for Team #{} and loaded {} camera(s)\n", config.team, config.cameraConfigs.size());

    // frc::CameraServer::SetSize(frc::CameraServer::kSize160x120);

    for (const auto &cconfig : config.cameraConfigs) {
        config.cameras.emplace_back(Camera(cconfig));
    }

    if (config.cameras.size()) {
        fmt::print("Created thread\n");
        std::thread([&] {
            frc::VisionRunner<BVPipeline> runner(config.cameras[0], new BVPipeline(), [&](BVPipeline &pipeline) {
                
            });

            runner.RunForever();
        }).detach();
    }

    for (;;) std::this_thread::sleep_for(std::chrono::seconds(10));
    
    return 0;
} // main