#include <iostream>

#include "engine/Physics.h"
#include "graphics/Window.h"
#include "graphics/Renderer.h"
#include "graphics/CameraController.h"

#include "config/Config.h"

int main(){
    Config::load("configuration/config.json");

    Physics physics;
    physics.importBodies(Config::simulation.inputData);

    Window window;
    Input input(window.getNativeWindow());
    Camera camera;
    CameraController cameraController;

    Renderer renderer;

    while(!window.shouldClose()){
        cameraController.update(camera, input);

        physics.step();

        renderer.beginFrame(camera, window.getSize()[0], window.getSize()[1]);
        renderer.render(physics.getBodies());

        window.update();
    }
}