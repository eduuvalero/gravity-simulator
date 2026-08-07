#include "graphics/VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, std::size_t size, GLenum usage){
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBuffer::~VertexBuffer() { 
    glDeleteBuffers(1, &id); 
};

void VertexBuffer::bind() const { 
    glBindBuffer(GL_ARRAY_BUFFER, id); 
};

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
};