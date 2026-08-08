#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/Window.h"
#include "graphics/Input.h"
#include "graphics/Renderer.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "graphics/CameraController.h"

int main()
{
    Window window(800, 600, "Gravity Simulator - Camera Test");
    Input input(window.getNativeWindow());

    // Start with the cursor visible.
    input.setCursorCaptured(false);

    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}
    };

    std::vector<unsigned int> indices = {
        0, 1, 2
    };

    Mesh mesh(vertices, indices);

    Shader shader(
        "shaders/default.vert",
        "shaders/default.frag"
    );

    Renderer renderer;
    Camera camera({0.0f, 0.0f, 40.0f});

    CameraController cameraController(10,
        0.002f
    );

    double lastTime = glfwGetTime();

    while (!window.shouldClose()){
        const double currentTime = glfwGetTime();

        const float deltaTime = static_cast<float>(currentTime - lastTime);

        lastTime = currentTime;
        cameraController.update(camera, input, deltaTime);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        const glm::ivec2 windowSize = window.getSize();
        const float aspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
        glViewport(0, 0, windowSize.x, windowSize.y);

        const glm::mat4 model = glm::mat4(1.0f);
        const glm::mat4 view = camera.getViewMatrix();
        const glm::mat4 projection = camera.getProjectionMatrix(aspectRatio);
        

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        renderer.draw(mesh, shader);

        window.update();
    }

    return 0;
}