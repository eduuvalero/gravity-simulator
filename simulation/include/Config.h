#ifndef CONFIG_H
#define CONFIG_H

namespace config{
    // Gravity
    constexpr double G = 1.0;
    constexpr double THETA = 0.5;
    constexpr double SOFTENING = 0.001;


    // Octree
    constexpr int CAPACITY = 1;
    constexpr double MINHALFWIDTH = 1e-6;


    // Simulation
    constexpr double DEFAULT_DT = 0.01;
}

#endif