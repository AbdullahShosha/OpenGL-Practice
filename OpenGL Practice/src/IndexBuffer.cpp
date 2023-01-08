#include "IndexBuffer.h"
#include"Renderer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count):Count(count)
{
    glGenBuffers(1, &RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); 
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &RendererID);
}

void IndexBuffer::bind()const 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
}

void IndexBuffer::unbind()const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
inline int IndexBuffer::GetCount()const 
{
    return Count;
}
