//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include <string>
#include <memory>
#include "../OpenGL/include/glm/glm.hpp"

class Shader
{
public:
    unsigned int id;

    void use() const;
    void uniformMatrix(const std::string& name, glm::mat4 matrix) const;
    void uniform1i(const std::string& name, int x) const;
    void uniform1f(const std::string& name, float x) const;
    void uniform2f(const std::string& name, float x, float y) const;
    void uniform3f(const std::string& name, float x, float y, float z) const;

    static void load_shader(const std::string &vertexFile, const std::string &fragmentFile, std::shared_ptr<Shader>& target);

    explicit Shader(unsigned int id);
    ~Shader();
};

//extern void
//load_shader(const std::string &vertexFile, const std::string &fragmentFile, std::shared_ptr<Shader>& target);

#endif //GRAPHICS_SHADER_H
