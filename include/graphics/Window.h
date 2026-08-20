#pragma once

#include <string>
#include "Glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "config/Config.h"


class Window{
    private:
        GLFWwindow* window_;
    public:
        Window(int width = Config::window.width, int height = Config::window.height, const std::string& title = Config::window.title);
        ~Window();
        bool shouldClose() const;
        void update();
        GLFWwindow* getNativeWindow() const;
        glm::ivec2 getSize() const;
};