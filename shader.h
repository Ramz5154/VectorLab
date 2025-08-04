#pragma once
#include <glad/glad.h>
#include <string>


class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(){}
    void use();
    void setMat4(const std::string& name, const float* value);
};
