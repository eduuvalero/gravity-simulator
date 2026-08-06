#include "graphics/Window.h"

#include <iostream>

#include <glad/glad.h>


Window::Window(int width, int height, const std::string& title){
    if (!glfwInit()){
        throw std::runtime_error(
            "Failed to initialize GLFW"
        );
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = glfwCreateWindow(width,height,title.c_str(),nullptr,nullptr);

    if (!window_){
        glfwTerminate();
        throw std::runtime_error(
            "Failed to create GLFW window"
        );
    }

    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress) ){
        throw std::runtime_error(
            "Failed to initialize GLAD"
        );
    }


    glfwSwapInterval(1); 
}



Window::~Window(){
    glfwDestroyWindow(window_);
    glfwTerminate();
}



bool Window::shouldClose() const{
    return glfwWindowShouldClose(window_);
}



void Window::update(){
    glfwSwapBuffers(window_);
    glfwPollEvents();
}



GLFWwindow* Window::getNativeWindow() const{
    return window_;
}