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
    physics.importBodies("assets/io/input.csv");

    Window window(Config::render.width, Config::render.height, "Gravity Simulator");

    Input input(window.getNativeWindow());
    Camera camera({0.0f, 0.0f, 300.0f});
    CameraController cameraController(Config::camera.moveSpeed, Config::camera.mouseSensitivity);

    Renderer renderer;

    while(!window.shouldClose()){
        cameraController.update(camera, input, Config::simulation.dt);

        physics.step(Config::simulation.dt);

        renderer.beginFrame(camera, window.getSize()[0], window.getSize()[1]);
        renderer.render(physics.getBodies());

        window.update();
    }
}