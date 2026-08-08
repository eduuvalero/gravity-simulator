#pragma once

#include <vector>

#include "Mesh.h"
#include "SphereMesh.h"
#include "Shader.h"
#include "Camera.h"
#include "engine/Body.h"

class Renderer{
    public:
        Renderer();
        void beginFrame(const Camera& camera, int width, int height);
        void render(const std::vector<Body>& bodies);
        void endFrame();
    private:
        void draw(const Mesh& mesh, const Shader& shader);
        void renderSphere(const SphereMesh& sphere, Shader& shader, const glm::vec3& position, float radius, const glm::vec3& color);
        
        SphereMesh sphere;
        Shader planetShader;
        Shader starShader;
        glm::mat4 view;
        glm::mat4 projection;
};