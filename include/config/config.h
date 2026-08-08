#pragma once

#include <string>

struct SimulationConfig {
    double dt;
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

struct RenderConfig {
    int width;
    int height;
    bool vsync;
};

struct CameraConfig {
    float moveSpeed;
    float mouseSensitivity;
};


class Config {
public:
    static SimulationConfig simulation;
    static PhysicsConfig physics;
    static OctreeConfig octree;
    static RenderConfig render;
    static CameraConfig camera;

    static void load(const std::string& path);
};