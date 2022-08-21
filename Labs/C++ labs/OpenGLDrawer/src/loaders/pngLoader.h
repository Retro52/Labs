//
// Created by Anton on 13.12.2021.
//

#ifndef GRAPHICS_PNGLOADER_H
#define GRAPHICS_PNGLOADER_H


#include <string>


class pngLoader
{
public:
    static int _png_load(const char *file, int *width, int *height);
//    static void load_texture(const std::string &filename, std::shared_ptr<Texture> &target);
};
#endif //GRAPHICS_PNGLOADER_H
