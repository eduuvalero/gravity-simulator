#pragma once

#include <string>
#include "math/Vector3.h"

struct SimulationConfig {
    float dt;
};

struct PhysicsConfig {
    double gravitationalConstant;
    double softening;
    double barnesHutTheta;
};

struct OctreeConfig {
    int capacity;
    double minimumHalfWidth;
};

struct WindowConfig {
    int width;
    int height;
    std::string title;
    bool vsync;
};

struct CameraConfig {
    std::vector<float> position;
    float moveSpeed;
    float mouseSensitivity;
};

class Config {
    public:
        static SimulationConfig simulation;
        static PhysicsConfig physics;
        static OctreeConfig octree;
        static WindowConfig window;
        static CameraConfig camera;

        static void load(const std::string& path);
};