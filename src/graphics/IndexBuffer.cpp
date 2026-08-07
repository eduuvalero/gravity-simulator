#include "graphics/IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, std::size_t size, GLenum usage){
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}


IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &id);
}

void IndexBuffer::bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}