#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/Physics.h"
#include "engine/Body.h"

#include "config/Config.h"

using namespace std;

int main(){
    Config::load("config/config.json");
    Physics physics;

    Body sun;
    sun.mass = 1000.0;
    sun.position = {0.0, 0.0, 0.0};
    sun.velocity = {0.0, 0.0, 0.0};

    Body earth;
    earth.mass = 1.0;
    earth.position = {20.0, 0.0, 0.0};
    earth.velocity = {0.0, 7.1, 0.0};

    Body moon;
    moon.mass = 0.0123;
    moon.position = {22.0, 0.0, 0.0};
    moon.velocity = {0.0, 8.0, 0.0};

    physics.addBody(&sun);
    physics.addBody(&earth);
    physics.addBody(&moon);

    const double dt = Config::simulation.dt;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Gravity Simulator", nullptr, nullptr);

    if (!window){
        std::cerr << "Failed to create window\n";

        glfwTerminate();

        return -1;
    }

    return 0;
}