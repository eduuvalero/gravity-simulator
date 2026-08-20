#include <emscripten.h>

#include "engine/Physics.h"
#include "graphics/Window.h"
#include "graphics/Renderer.h"
#include "graphics/CameraController.h"

#include "config/Config.h"

static Physics* physics = nullptr;
static Window* window = nullptr;
static Input* input = nullptr;
static Camera* camera = nullptr;
static CameraController* cameraController = nullptr;
static Renderer* renderer = nullptr;

void webMainLoop() {
    cameraController->update(*camera, *input);

    physics->step();

    renderer->beginFrame(*camera, window->getSize()[0], window->getSize()[1]);
    renderer->render(physics->getBodies());

    window->update();
}

int main() {

    Config::load("configuration/config.json");

    Physics physicsInstance;
    physicsInstance.importBodies("assets/data/input_web.csv");

    Window windowInstance;
    Input inputInstance(windowInstance.getNativeWindow());

    Camera cameraInstance;
    CameraController cameraControllerInstance;

    Renderer rendererInstance;

    physics = &physicsInstance;
    window = &windowInstance;
    input = &inputInstance;
    camera = &cameraInstance;
    cameraController = &cameraControllerInstance;
    renderer = &rendererInstance;

    emscripten_set_main_loop(webMainLoop,0,true);

    return 0;
}