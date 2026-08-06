#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/Physics.h"

#include "config/Config.h"

using namespace std;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
    }

int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Gravity Simulator", nullptr, nullptr);
    if(window == nullptr){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}