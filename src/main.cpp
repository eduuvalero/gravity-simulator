#include <iostream>

#include "engine/Physics.h"
#include "graphics/Window.h"
#include "graphics/Input.h"
#include "graphics/Renderer.h"
#include "graphics/Camera.h"
#include "graphics/CameraController.h"
#include "io/CSVImporter.h"

#include "config/Config.h"

int main(){
    Config::load("config/config.json");

    Physics physics;
    physics.importBodies("config/input.csv");

    Window window(Config::render.width, Config::render.height,"Grasity Simulator");
    Input input(window.getNativeWindow());
    Camera camera({0.0f, 0.0f,  3.0f});
    CameraController cameraController(Config::camera.moveSpeed, Config::camera.mouseSensitivity);

    while(!window.shouldClose()){
        window.getNativeWindow();

        cameraController.update(camera, input,  Config::simulation.dt);

        physics.step(Config::simulation.dt);

        window.update();
    };
};