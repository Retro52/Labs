//
// Created by Anton on 12.12.2021.
//

#define GLEW_STATIC
#include "Texture.h"
#include "../OpenGL/include/GLEW/glew.h"

Texture::Texture(unsigned int id, int width, int height) : id(id), width(width), height(height)
{
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}
