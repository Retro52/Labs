//
// Created by Anton on 12.12.2021.
//

#define GLEW_STATIC
#include "Texture.h"
#include "../OpenGL/include/GLEW/glew.h"

/**
 * Texture class constructor
 * @param id texture id
 * @param width texture width
 * @param height texture height
 */
Texture::Texture(unsigned int id, int width, int height) : id(id), width(width), height(height) {}

/**
 * Texture class deconstructor, deletes texture from gl memory
 */
Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

/**
 * Sets texture as current for OpenGL
 */
void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}
