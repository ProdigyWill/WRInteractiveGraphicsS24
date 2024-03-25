#pragma once
#include <glad/glad.h> 
#include <vector>
#include <unordered_map>
#include <string>
#include "Texture.h"
class IndexBuffer
{
protected:
	unsigned int iboId;
	std::vector<unsigned short> indexData;
	unsigned int numberOfIndexes;
public:
	IndexBuffer();
	~IndexBuffer();

	inline void Select() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId); }
	inline void Deselect() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	inline const std::vector<unsigned short>& GetIndexData() { return indexData; }
	inline unsigned int GetNumberOfVertices() const { return numberOfIndexes; }
	void AddIndexData(unsigned int count, ...);
	void AddIndexData(unsigned short index);
	void StaticAllocate();
};


