//
// Created by Anton on 19.08.2022.
//

#include "Model.h"
#include "../Logging/easylogging++.h"
#include "../Loaders/cwalk.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
    string filename = string(path);
    stbi_set_flip_vertically_on_load(true);

    LOG(DEBUG) << "Generated path: " << path;
    LOG(DEBUG) << "Generated directory: " << directory;
    filename = directory + '/' + filename;

    LOG(DEBUG) << "Generated filename: " << filename;

    unsigned int textureID;

    glGenTextures(1, &textureID);
    int width, height, nrComponents;

    char actualpath [PATH_MAX + 1];
    cwk_path_get_absolute(R"(C:\)", filename.c_str(), actualpath, sizeof(actualpath));
    unsigned char * data = stbi_load(actualpath, &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        LOG(ERROR) << "Texture failed to load at path: " << actualpath << std::endl;
        LOG(ERROR) << stbi_failure_reason();
        stbi_image_free(data);
    }

    return textureID;
}