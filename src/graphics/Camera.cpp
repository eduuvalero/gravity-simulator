#include "graphics/Camera.h"

Camera::Camera(glm::vec3 position) : position(position), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) {}

glm::vec3 Camera::getFront() const{
    return rotation * glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 Camera::getUp() const{
    return rotation * glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(position, position + getFront(), getUp());
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const{
    return glm::perspective(glm::radians(45.0f), aspectRatio,0.1f, 1000.0f);
}

void Camera::move(const glm::vec3& direction, float amount){
    position += (rotation * direction) * amount;
}

void Camera::rotate(float angle, const glm::vec3& axis){
    glm::quat q = glm::angleAxis(angle, glm::normalize(axis));
    rotation = rotation * q;
}