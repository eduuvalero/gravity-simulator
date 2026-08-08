#include "graphics/Renderer.h"

void Renderer::draw(const Mesh& mesh, const Shader& shader){
    shader.use();
    mesh.draw();
}