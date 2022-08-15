//
// Created by Anton on 12.12.2021.
//

#define GLEW_STATIC

#include <iostream>
#include "Texture.h"
#include "../OpenGL/include/GLEW/glew.h"
#include "../loaders/pngLoader.h"

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

int Texture::load_texture(const std::string &filename, std::shared_ptr<Texture> &target)
{
    int width, height;
    GLuint texture = pngLoader::_png_load(filename.c_str(), &width, &height);
    if (texture == 0)
    {
        std::cerr << "[ERROR]::TEXTURE Could not load texture: " << filename << std::endl;
        return -1;
    }
    target = std::move(std::make_shared<Texture>(texture, width, height));
    return 0;
}