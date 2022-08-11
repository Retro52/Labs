//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H


#include <string>
#include <memory>

class Texture
{
public:
    unsigned int id;
    int width;
    int height;
    Texture() = default;
    Texture(unsigned int id, int width, int height);
    ~Texture();

    void bind() const;
};

#endif //GRAPHICS_TEXTURE_H
