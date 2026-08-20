#include "graphics/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

static glm::vec3 toGlmVec3(const Vec3d& v){
    return glm::vec3(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z));
}

static glm::vec3 toGlmVec3(const Vec3f& v){
    return glm::vec3(v.x, v.y, v.z);
}

Renderer::Renderer() : sphere(32, 16), planetShader("assets/shaders/sphere.vert", "assets/shaders/planet.frag"), 
                        starShader("assets/shaders/sphere.vert","assets/shaders/star.frag") {}

void Renderer::renderSphere(const SphereMesh& sphere, Shader& shader, const glm::vec3& position, float radius, const glm::vec3& color){
    shader.use();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(radius));

    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.setVec3("color", color);

    sphere.getMesh().draw();
}

void Renderer::beginFrame(const Camera& camera, int width, int height){
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    view = camera.getViewMatrix();
    projection = camera.getProjectionMatrix(aspectRatio);
};

void Renderer::render(const std::vector<Body>& bodies){
    lightManager.clear();

    for (const Body& body : bodies){
        if (!body.alive || body.type != BodyType::Star){
            continue;
        }

        Light light;
        light.position = toGlmVec3(body.position);
        light.intensity = static_cast<float>(body.radius * body.radius) * Config::lightning.intensityScale;

        lightManager.addLight(light);
    }

    for (std::size_t i = 0; i < bodies.size(); ++i) {
        const Body& body = bodies[i];
        if (!body.alive){
            continue;
        }

        glm::vec3 position = toGlmVec3(body.position);
        glm::vec3 color = toGlmVec3(body.color);

        if (body.type == BodyType::Star){
            renderSphere(sphere, starShader, position, static_cast<float>(body.radius), color);
        }
        else if (body.type == BodyType::Planet){
            const auto relevantLights = lightManager.getRelevantLights(position, 1);

            planetShader.use();

            planetShader.setInt("lightCount", static_cast<int>(relevantLights.size()));

            for (std::size_t i = 0; i < relevantLights.size(); ++i){
                const Light& light = lightManager.getLight(relevantLights[i]);

                planetShader.setVec3("lights[" + std::to_string(i) + "].position", light.position);
                planetShader.setFloat("lights[" + std::to_string(i) + "].intensity", light.intensity);
            }

            renderSphere(sphere, planetShader, position, static_cast<float>(body.radius), color);
        }
    }
}

