//
// Created by Anton on 16.08.2022.
//

#ifndef GRAPHICS_UIHANDLER_H
#define GRAPHICS_UIHANDLER_H

#include <iostream>
#include <map>
#include <ft2build.h>
#include <memory>
#include FT_FREETYPE_H
#include "../OpenGL/include/glm/glm.hpp"
#include "../Render/Shader.h"


struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class UIHandler
{
private:
    static std::map<char, Character> Characters;
    static unsigned int VAO, VBO;
//    unsigned int VAO, VBO;

private:
    // render state
public:
    static int Initialize();
//    static void RenderText(const Shader& shader, const std::string &text, float x, float y, float scale, const glm::vec3 &color, unsigned int VAO, unsigned int VBO, std::map<char, Character> Characters);
    static void RenderText(Shader shader, const std::string &text, float x, float y, float scale, const glm::vec3 &color);
//    static void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
//    static void RenderText(const std::shared_ptr<Shader> &s, const std::string &text, float x, float y, float scale, const glm::vec3 &color = glm::vec3(1.0f));
    // pre-compiles a list of characters from the given font
    void Load(std::string font, unsigned int fontSize);
};


#endif //GRAPHICS_UIHANDLER_H
