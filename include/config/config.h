#pragma once

#include <string>
#include <vector>

struct SimulationConfig {
    float dt;
    std::string inputData;
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
    float renderDistance;
};

struct LightningConfig{
    float cellSize;
    float softening;
    float threshold;
    int intensityScale;
};

class Config {
    public:
        static SimulationConfig simulation;
        static PhysicsConfig physics;
        static OctreeConfig octree;
        static WindowConfig window;
        static CameraConfig camera;
        static LightningConfig lightning;

        static void load(const std::string& path);
};