//
// Created by Anton on 12.12.2021.
//
#define GLEW_STATIC

#include "Shader.h"


#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "../OpenGL/include/GLEW/glew.h"
#include "../OpenGL/include/glm/gtc/type_ptr.hpp"

/**
 * Shader constructor
 * @param id new shader id
 */
Shader::Shader(unsigned int id) : id(id) {}

/**
 * Shader deconstructor, deletes shader from gl memory
 */
Shader::~Shader()
{
    glDeleteProgram(id);
}

/**
 * Set this shader as current for OpenGL
 */
void Shader::use() const
{
    glUseProgram(id);
}

/**
 * Send a four dimensional matrix to the shader
 * @param name value name in shader
 * @param matrix value to send
 */
void Shader::uniformMatrix(const std::string& name, glm::mat4 matrix) const
{
    GLuint transformLoc = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

/**
 * Send an integer to the shader
 * @param name value name in shader
 * @param x value to send
 */
void Shader::uniform1i(const std::string& name, int x) const
{
    GLuint transformLoc = glGetUniformLocation(id, name.c_str());
    glUniform1i(transformLoc, x);
}

/**
 * Send a float to the shader
 * @param name value name in shader
 * @param x value to send
 */
void Shader::uniform1f(const std::string& name, float x) const
{
    GLuint transformLoc = glGetUniformLocation(id, name.c_str());
    glUniform1f(transformLoc, x);
}

/**
 * Send two floats to the shader
 * @param name values name in shader
 * @param x first value to send
 * @param y second value to send
 */
void Shader::uniform2f(const std::string& name, float x, float y) const
{
    GLuint transformLoc = glGetUniformLocation(id, name.c_str());
    glUniform2f(transformLoc, x, y);
}

/**
 * Send three floats to the shader
 * @param name values name in shader
 * @param x first value to send
 * @param y second value to send
 * @param z third value to send
 */
void Shader::uniform3f(const std::string& name, float x, float y, float z) const
{
    GLuint transformLoc = glGetUniformLocation(id, name.c_str());
    glUniform3f(transformLoc, x,y,z);
}

/**
 * load and compile shader
 * @param vertexFile path to the vertex shader file
 * @param fragmentFile path to the fragment shader file
 * @param target shared pointer to the shader object, to write data into
 */
void Shader::load_shader(const std::string &vertexFile, const std::string &fragmentFile, std::shared_ptr<Shader>& target)
{
    // Reading Files
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexFile, std::ios::in);
        fShaderFile.open(fragmentFile, std::ios::in);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    }
    catch(std::ifstream::failure& e)
    {
        std::cerr << "[ERROR]::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        return;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "[ERROR]::SHADER::VERTEX: compilation failed" << std::endl;
        std::cerr << infoLog << std::endl;
        return;
    }

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "[ERROR]::SHADER::FRAGMENT: compilation failed" << std::endl;
        std::cerr << infoLog << std::endl;
        return;
    }

    // Shader Program
    GLuint id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "[ERROR]::SHADER::PROGRAM: linking failed" << std::endl;
        std::cerr << infoLog << std::endl;

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    target = std::move(std::make_shared<Shader>(id));
}