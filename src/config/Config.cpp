#include "config/Config.h"

#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

SimulationConfig Config::simulation;
PhysicsConfig Config::physics;
OctreeConfig Config::octree;
RenderConfig Config::render;
CameraConfig Config::camera;

void Config::load(const std::string& path){
    std::ifstream file(path);

    if (!file.is_open())
        throw std::runtime_error("Could not open config file.");

    json j;
    file >> j;

    simulation.dt = j.at("simulation").at("dt").get<double>();

    physics.gravitationalConstant = j.at("physics").at("gravitationalConstant").get<double>();
    physics.softening =j.at("physics").at("softening").get<double>();
    physics.barnesHutTheta = j.at("physics").at("barnesHutTheta").get<double>();

    octree.capacity = j.at("octree").at("capacity").get<int>();
    octree.minimumHalfWidth = j.at("octree").at("minimumHalfWidth").get<double>();

    render.width = j.at("render").at("width").get<int>();
    render.height = j.at("render").at("height").get<int>();
    render.vsync = j.at("render").at("vsync").get<bool>();

    camera.moveSpeed = j.at("camera").at("moveSpeed").get<float>();
    camera.mouseSensitivity = j.at("camera").at("mouseSensitivity").get<float>();
}