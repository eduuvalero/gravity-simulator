#pragma once

#include "Glad.h"

#include <vector>

class IndexBuffer{
    public:
        IndexBuffer(const void* data, std::size_t size, GLenum usage = GL_STATIC_DRAW);

        template<typename T>
        explicit IndexBuffer(const std::vector<T>& data,GLenum usage = GL_STATIC_DRAW): IndexBuffer(data.data(), data.size() * sizeof(T), usage){}
    
        ~IndexBuffer();
        void bind() const;
        static void unbind();
    private:
        GLuint id;
};