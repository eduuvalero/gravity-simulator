#pragma once

#include <vector>
#include <glad/glad.h>

class VertexBuffer{
    public:
        VertexBuffer(const void *data, std::size_t size, GLenum usage = GL_STATIC_DRAW);

        template <typename T>
        explicit VertexBuffer(const std::vector<T> &data, GLenum usage = GL_STATIC_DRAW) : VertexBuffer(data.data(), data.size() * sizeof(T), usage) {}
        ~VertexBuffer();
        void bind() const;
        static void unbind();
    private:
        GLuint id;
};