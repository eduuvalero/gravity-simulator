#pragma once

#include <graphics/Vertex.h>
#include <graphics/VertexBuffer.h>
#include <graphics/VertexArray.h>
#include <graphics/IndexBuffer.h>

class Mesh{
    private:
        VertexArray VAO;
        VertexBuffer VBO;
        IndexBuffer EBO;
        std::size_t indexCount;
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indexData);
        void draw() const;
};