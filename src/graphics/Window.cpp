#include "graphics/Window.h"

#include "graphics/Renderer.h"
#include "config/Config.h"

Window::Window(int width, int height, const std::string& title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

#ifdef __EMSCRIPTEN__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#endif

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window_) {
        std::cerr << "ERROR: glfwCreateWindow()" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window_);

#ifndef __EMSCRIPTEN__
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
#endif

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

#ifndef __EMSCRIPTEN__
    glfwSwapInterval(Config::window.vsync);
#endif
}

Window::~Window() {

    if (window_) {
        glfwDestroyWindow(window_);
    }

    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window_);
}

void Window::update() {
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

GLFWwindow* Window::getNativeWindow() const {
    return window_;
}

glm::ivec2 Window::getSize() const {
    int width;
    int height;

    glfwGetFramebufferSize(window_, &width, &height);

    return {width, height};
}