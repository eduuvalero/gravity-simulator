#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "config/Config.h"

class Camera{
    private:
        glm::vec3 position;
        glm::quat rotation;

        glm::vec3 getFront() const;
        glm::vec3 getUp() const;
    public:
        Camera(glm::vec3 position = {Config::camera.position[0], Config::camera.position[1], Config::camera.position[2]});
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix(float aspectRatio) const;

        void move(const glm::vec3& direction, float amount);
        void rotate(float angle, const glm::vec3& axis);
};