#include "graphics/Input.h"

#include <unordered_set>

Input::Input(GLFWwindow* window) : window(window), previousMousePosition(getMousePosition()) {}

bool Input::isKeyPressed(int key) const{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::isKeyJustPressed(int key){
    const bool pressed = isKeyPressed(key);
    const bool wasPressed = previousKeys.contains(key);

    if(pressed){
        previousKeys.insert(key);
    }
    else{
        previousKeys.erase(key);
    }

    return pressed && !wasPressed;
}

bool Input::isMouseButtonPressed(int button) const{
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

glm::vec2 Input::getMousePosition() const{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return {static_cast<float>(x), static_cast<float>(y)};
}

glm::vec2 Input::getMouseDelta(){
    const glm::vec2 currentPosition = getMousePosition();
    const glm::vec2 delta = currentPosition - previousMousePosition;

    previousMousePosition = currentPosition;

    return delta;
}

bool Input::isFocused() const {
    return glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE;
}

void Input::setCursorCaptured(bool captured){
    glfwSetInputMode(window, GLFW_CURSOR, captured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    cursorCaptured_ = captured;
    previousMousePosition = getMousePosition();
}

bool Input::isCursorCaptured() const{
    return cursorCaptured_;
}