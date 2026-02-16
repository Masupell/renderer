#include "shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

void check_shader_compilation(unsigned int shader);
void check_linking_compilation(unsigned int shaderProgram);

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    try
    {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vertexShaderStream, fragmentShaderStream;

        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "File not read:\n" << e.what() << std::endl;
    }
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    check_shader_compilation(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    check_shader_compilation(fragmentShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    check_linking_compilation(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::use()
{
    glUseProgram(ID);
}

unsigned int Shader::getID()
{
    return ID;
}

void Shader::setInt(const char* name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const char* name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setmatrix4fv(const char* name, const glm::mat4& value)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

int Shader::getUniformLocation(const char* name)
{
    std::string key(name);

    auto it = uniformCache.find(key);
    if (it != uniformCache.end()) { return it->second; }

    int location = glGetUniformLocation(ID, name);
    uniformCache[key] = location;

    return location;
}

void check_shader_compilation(unsigned int shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Shader Compilation Failed:\n" << infoLog << std::endl;
    }
}

void check_linking_compilation(unsigned int shaderID)
{
    int success;
    char infoLog[512];
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "Shader Linking Failed:\n" << infoLog << std::endl;
    }
}