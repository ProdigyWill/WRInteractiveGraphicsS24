#pragma once
#include "BaseObject.h"
#include <glad/glad.h>
class Texture : public BaseObject
{
private:
	unsigned char* textureData;
	unsigned int textureId;
	unsigned int type = GL_TEXTURE_2D, 
		width = 0, 
		height = 0, 
		internalFormat = GL_RGBA8, 
		sourceFormat = GL_RGBA, 
		wrapS = GL_REPEAT, 
		wrapT = GL_REPEAT, 
		magFilter = GL_NEAREST,
		minFilter = GL_NEAREST;
	bool isLoadedFromFile = false;
	
public:
	Texture();
	~Texture();
	inline unsigned char* GetTextureData() const { return textureData; }
	inline unsigned int GetTextureId() const { return textureId; }
	inline bool IsLoadedFromFile() const { return isLoadedFromFile; }
	void SetWidth(int width);
	void setHeight(int height);
	void SelectToChange();
	void Deselect();
	void SelectToRender(int textureUnit = 0);
	void Allocate();
	void SetTextureData(unsigned int count, unsigned char* data);
private:
	void CleanUp();
};

