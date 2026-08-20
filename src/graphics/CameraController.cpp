#include "graphics/CameraController.h"

CameraController::CameraController(float moveSpeed, float mouseSensitivity) : moveSpeed(moveSpeed), mouseSensitivity(mouseSensitivity) {}

void CameraController::update(Camera& camera, Input& input, float deltaTime) {
    if (input.isCursorCaptured() && input.isKeyPressed(GLFW_KEY_ESCAPE)){
        input.setCursorCaptured(false);
        return;
    }

    if (!input.isFocused()){
        return;
    }

    if (!input.isCursorCaptured()) {
        if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
            input.setCursorCaptured(true);
        }
        return;
    }

    if (input.isKeyPressed(GLFW_KEY_W)){
        camera.move(glm::vec3(0.0f, 0.0f, -1.0f), moveSpeed * deltaTime);
    }
    if (input.isKeyPressed(GLFW_KEY_S)) {
        camera.move(glm::vec3(0.0f, 0.0f, 1.0f), moveSpeed * deltaTime);
    }
    if (input.isKeyPressed(GLFW_KEY_A)) {
        camera.move(glm::vec3(-1.0f, 0.0f, 0.0f), moveSpeed * deltaTime);
    }
    if (input.isKeyPressed(GLFW_KEY_D)) {
        camera.move(glm::vec3(1.0f, 0.0f, 0.0f), moveSpeed * deltaTime);
    }
    if (input.isKeyPressed(GLFW_KEY_SPACE)) {
        camera.move(glm::vec3(0.0f, 1.0f, 0.0f), moveSpeed * deltaTime);
    }
    if (input.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
        camera.move(glm::vec3(0.0f, -1.0f, 0.0f), moveSpeed * deltaTime);
    }

    const glm::vec2 mouseDelta = input.getMouseDelta();

    camera.rotate(-mouseDelta.x * mouseSensitivity, glm::vec3(0.0f, 1.0f, 0.0f));
    camera.rotate(-mouseDelta.y * mouseSensitivity, glm::vec3(1.0f, 0.0f, 0.0f));
}