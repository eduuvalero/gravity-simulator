#include "graphics/Shader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath){
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
};

std::string Shader::readFile(const std::string& path){
    std::ifstream file(path);
    std::stringstream ss;

    if (!file.is_open()) {
        throw std::runtime_error("Couldn't open shader file: " + path);
    }

    ss << file.rdbuf();

    return ss.str();
};