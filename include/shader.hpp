#pragma once

class Shader
{
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        void use();
        unsigned int getID();
        // All temporary
        void setInt(const char* name, int value);
        void setFloat(const char* name, float value);
        void setmatrix4fv(const char* name, const float* value);
        ~Shader();
    
    private:
        unsigned int ID;
};