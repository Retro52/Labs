//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H
#define GLEW_STATIC

#include <string>
#include <memory>
#include <vector>
//#include "../lights/DirectionalLight.h"
//#include "../lights/PointLight.h"
#include "../OpenGL/include/glm/glm.hpp"
#include "../lights/DirectionalLight.h"
#include "../lights/PointLight.h"
//#include "../OpenGL/include/GLEW/glew.h"


class Shader
{
public:
    unsigned int id;

    void use() const;
    void uniformMatrix(const std::string& name, glm::mat4 matrix) const;
    void uniform1i(const std::string& name, int x) const;
    void uniform1b(const std::string& name, bool x) const;
    void uniform1f(const std::string& name, float x) const;
    void uniform2f(const std::string& name, float x, float y) const;
    void uniform3f(const std::string& name, float x, float y, float z) const;

    void uniform1dl(const std::shared_ptr<DirectionalLight> &dirLight) const;
    void uniform1pl(int idx, const std::shared_ptr<PointLight> &pointLight) const;
    void uniformnpl(const std::vector<std::shared_ptr<PointLight>> &pointLights) const;

    static int load_shader(const std::string &vertexFile, const std::string &fragmentFile, std::shared_ptr<Shader>& target);

    explicit Shader(unsigned int id);
    ~Shader();
};

//extern void
//load_shader(const std::string &vertexFile, const std::string &fragmentFile, std::shared_ptr<Shader>& target);

#endif //GRAPHICS_SHADER_H
