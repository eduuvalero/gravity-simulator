#pragma once

#include "graphics/Mesh.h"
#include "graphics/Shader.h"

class Renderer{
    public:
        void draw(const Mesh& mesh, const Shader& shader);
};