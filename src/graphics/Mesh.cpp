#include <graphics/Mesh.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indexData) : VBO(vertices), EBO(indexData), indexCount(indexData.size()){
    VAO.bind();
    VBO.bind();
    EBO.bind();

    VAO.addAttribute(0, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, position)));
    VAO.addAttribute(1, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, normal)));
    VAO.addAttribute(2, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, color)));
}

void Mesh::draw() const{
    VAO.bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}