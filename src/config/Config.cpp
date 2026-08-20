#include "config/Config.h"

#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

SimulationConfig Config::simulation;
PhysicsConfig Config::physics;
OctreeConfig Config::octree;
WindowConfig Config::window;
CameraConfig Config::camera;
LightningConfig Config::lightning;

void Config::load(const std::string& path){
    std::ifstream file(path);

    if (!file.is_open())
        throw std::runtime_error("Could not open config file.");

    json j;
    file >> j;

    simulation.dt = j.at("simulation").at("dt").get<double>();
    simulation.inputData = j.at("simulation").at("inputData").get<std::string>();

    physics.gravitationalConstant = j.at("physics").at("gravitationalConstant").get<double>();
    physics.softening =j.at("physics").at("softening").get<double>();
    physics.barnesHutTheta = j.at("physics").at("barnesHutTheta").get<double>();

    octree.capacity = j.at("octree").at("capacity").get<int>();
    octree.minimumHalfWidth = j.at("octree").at("minimumHalfWidth").get<double>();

    window.width = j.at("window").at("width").get<int>();
    window.height = j.at("window").at("height").get<int>();
    window.title = j.at("window").at("title").get<std::string>();
    window.vsync = j.at("window").at("vsync").get<bool>();

    camera.position = {j.at("camera").at("position").get<std::vector<float>>()[0], j.at("camera").at("position").get<std::vector<float>>()[1], j.at("camera").at("position").get<std::vector<float>>()[2]};
    camera.moveSpeed = j.at("camera").at("moveSpeed").get<float>();
    camera.mouseSensitivity = j.at("camera").at("mouseSensitivity").get<float>();
    camera.renderDistance = j.at("camera").at("renderDistance").get<float>();

    lightning.cellSize = j.at("lightning").at("cellSize").get<float>();
    lightning.softening = j.at("lightning").at("softening").get<float>();
    lightning.threshold = j.at("lightning").at("threshold").get<float>();
    lightning.intensityScale = j.at("lightning").at("intensityScale").get<float>();
}