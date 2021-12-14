//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H


#include <string>

class Texture
{
public:
    unsigned int id;
    int width;
    int height;
    Texture(unsigned int id, int width, int height);
    Texture(unsigned char* data, int width, int height);
    ~Texture();

    void bind() const;
    void reload(unsigned char* data);
};

extern Texture* load_texture(const std::string& filename);


#endif //GRAPHICS_TEXTURE_H
