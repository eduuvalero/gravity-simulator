#include "graphics/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

void Renderer::draw(const Mesh& mesh, const Shader& shader){
    shader.use();
    mesh.draw();
}
void Renderer::drawSphere(const SphereMesh& sphere, Shader& shader, const glm::vec3& position, float radius, const glm::vec3& color){
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(radius));

    shader.setMat4("model", model);
    draw(sphere.getMesh(), shader);
}