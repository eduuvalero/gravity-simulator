#include "graphics/VertexArray.h"

VertexArray::VertexArray() { 
    glGenVertexArrays(1, &id); 
};

VertexArray::~VertexArray() { 
    glDeleteVertexArrays(1, &id); 
};

void VertexArray::bind() const { 
    glBindVertexArray(id); 
};

void VertexArray::unbind() { 
    glBindVertexArray(0); 
};

void VertexArray::addAttribute(GLuint index, GLint count, GLenum type, GLsizei stride, const void* offset){
    glVertexAttribPointer(index, count, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(index);
}