#pragma once

#include "Camera.h"
#include "Input.h"
#include "config/Config.h"

class CameraController{
    public:
        CameraController(float moveSpeed = Config::camera.moveSpeed, float mouseSensitivity = Config::camera.mouseSensitivity);
        void update(Camera& camera, Input& input, float deltaTime = Config::simulation.dt);
    private:
        float moveSpeed;
        float mouseSensitivity;
};