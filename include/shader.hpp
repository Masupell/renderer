#pragma once

#include <unordered_map>
#include <string>

class Shader
{
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        void use();
        unsigned int getID();
        void setInt(const char* name, int value);
        void setFloat(const char* name, float value);
        // Not safe
        void setmatrix4fv(const char* name, const float* value);
        int getUniformLocation(const char* name);
    
        ~Shader();
    
    private:
        unsigned int ID;
        std::unordered_map<std::string, int> uniformCache;
};