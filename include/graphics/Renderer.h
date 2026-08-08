#pragma once

#include "Mesh.h"
#include "SphereMesh.h"
#include "Shader.h"

class Renderer{
    public:
        void draw(const Mesh& mesh, const Shader& shader);
        void drawSphere(const SphereMesh& sphere, Shader& shader, const glm::vec3& position, float radius, const glm::vec3& color);
};