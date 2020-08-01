#include <Electrosim/IndexBuffer.hpp>
#define GLEW_STATIC
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : mCount(count) {



	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
	glDeleteBuffers(1,&mRendererID);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER,mRendererID);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
