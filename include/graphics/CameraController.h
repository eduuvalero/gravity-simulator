#pragma once

#include "Camera.h"
#include "Input.h"

class CameraController{
    public:
        CameraController(float moveSpeed, float mouseSensitivity);
        void update(Camera& camera, Input& input, float deltaTime);
    private:
        float moveSpeed;
        float mouseSensitivity;
};