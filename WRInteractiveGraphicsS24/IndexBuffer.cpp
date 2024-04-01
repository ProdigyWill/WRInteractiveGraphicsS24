#include "IndexBuffer.h"
#include <cstdarg>

IndexBuffer::IndexBuffer() {
	glGenBuffers(1, &iboId);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &iboId);
}

void IndexBuffer::AddIndexData(unsigned int count, ...)
{
	va_list args;
	va_start(args, count);
	while (count > 0) {
		indexData.push_back(static_cast<unsigned short>(va_arg(args, int)));
		count--;
	}
	va_end(args);
}

void IndexBuffer::AddIndexData(unsigned short index)
{
	indexData.push_back(index);
}

void IndexBuffer::StaticAllocate()
{
	unsigned long long bytesToAllocate = indexData.size() * sizeof(unsigned short);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesToAllocate, indexData.data(), GL_STATIC_DRAW);
}

