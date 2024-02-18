#include "Texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
	}
    else {
        stbi_image_free(textureData);
    }
    textureData = nullptr;
}

void Texture::SetWidth(int width)
{
    this->width = width;
}

void Texture::SetHeight(int height)
{
    this->height = height;
}

void Texture::SetWrapS(unsigned int wrapS)
{
    this->wrapS = wrapS;
}

void Texture::SetWrapT(unsigned int wrapT)
{
    this->wrapT = wrapT;
}

void Texture::SetMagFilter(unsigned int magFilter)
{
    this->magFilter = magFilter;
}

void Texture::SetMinFilter(unsigned int minFilter)
{
    this->minFilter = minFilter;
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

    glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);

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

void Texture::LoadTextureDataFromFile(const std::string& filepath)
{
    CleanUp();
    int width, height;
    stbi_set_flip_vertically_on_load(true);
    textureData = stbi_load(filepath.c_str(), &width, &height, &numberOfChannels, 0);
    this->width = width;
    this->height = height;
    if (numberOfChannels == 3) {
        sourceFormat = GL_RGB;
    }
    isLoadedFromFile = true;

}
