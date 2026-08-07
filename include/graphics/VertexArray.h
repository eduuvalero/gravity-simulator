#pragma once

#include <glad/glad.h>

class VertexArray{
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        static void unbind();
        void addAttribute(GLuint index, GLint count, GLenum type, GLsizei stride, const void* offset);
    private:
        GLuint id = 0;
};