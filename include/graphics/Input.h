#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <unordered_set>

class Input{
    public:
        explicit Input(GLFWwindow* window);

        bool isFocused() const;

        void setCursorCaptured(bool captured);
        bool isCursorCaptured() const;

        bool isKeyPressed(int key) const;
        bool isKeyJustPressed(int key);

        bool isMouseButtonPressed(int button) const;
        glm::vec2 getMousePosition() const;
        glm::vec2 getMouseDelta();

    private:
        GLFWwindow* window;

        bool cursorCaptured_ = false;

        std::unordered_set<int> previousKeys;

        glm::vec2 previousMousePosition;
};