#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window{
    private:
        GLFWwindow* window_;
    public:
        Window(int width, int height, const std::string& title);
        ~Window();
        bool shouldClose() const;
        void update();
        GLFWwindow* getNativeWindow() const;
};