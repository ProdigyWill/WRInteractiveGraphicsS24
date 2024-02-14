#include "Texture.h"
#include <glad/glad.h>
Texture::Texture() {
	this->textureData = nullptr;
    glGenTextures(1, &textureId);
}

Texture::~Texture() {
	CleanUp();
    glDeleteTextures(1, &textureId);
}

void Texture::CleanUp()
{
	if (textureData == nullptr) { return; }
	if (!isLoadedFromFile) { 
		delete[] textureData;
		textureData = nullptr;
	}
}

void Texture::SetWidth(int width)
{
    this->width = width;
}

void Texture::setHeight(int height)
{
    this->height = height;
}

void Texture::SelectToChange()
{
    glBindTexture(type, textureId);
}

void Texture::Deselect()
{
    glBindTexture(type, 0);
}

void Texture::SelectToRender(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(type, textureId);
}

void Texture::Allocate()
{
    SelectToChange();

    glTexParameteri(type, wrapS, GL_REPEAT);
    glTexParameteri(type, wrapT, GL_REPEAT);
    glTexParameteri(type, minFilter, GL_LINEAR);
    glTexParameteri(type, magFilter, GL_LINEAR);

    glTexImage2D(type, 0, internalFormat, width, height, 0, sourceFormat, GL_UNSIGNED_BYTE, textureData);

    CleanUp();

    glGenerateMipmap(type);

    Deselect();
}

void Texture::SetTextureData(unsigned int count, unsigned char* data) {
    CleanUp();
    textureData = new unsigned char[count];
    memcpy(textureData, data, count);
    isLoadedFromFile = false;
}
