#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera{
    private:
        glm::vec3 position;
        glm::quat rotation;

        glm::vec3 getFront() const;
        glm::vec3 getUp() const;
    public:
        Camera(glm::vec3 position);
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix(float aspectRatio) const;

        void move(const glm::vec3& direction, float amount);
        void rotate(float angle, const glm::vec3& axis);
};