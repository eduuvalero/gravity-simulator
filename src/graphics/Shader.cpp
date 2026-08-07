#include "graphics/Shader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath){
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;

    std::string vertexSrc = readFile(vertexPath);
    std::string fragmentSrc = readFile(fragmentPath);

    try{
        vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
        fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

        programID = linkProgram(vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    catch(...){
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        throw;
    }
};

GLuint Shader::compileShader(GLenum type, const std::string& source){
    GLuint shader = glCreateShader(type);
    const char* shaderSource = source.c_str();

    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    checkShader(shader);

    return shader;
}

GLuint Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader){
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    checkProgram(program);

    return program;
}

std::string Shader::readFile(const std::string& path){
    std::ifstream file(path);
    std::stringstream ss;

    if (!file.is_open()) {
        throw std::runtime_error("Couldn't open shader file: " + path);
    }

    ss << file.rdbuf();

    return ss.str();
}

void Shader::checkShader(GLuint shader){
    GLint success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::string log(logLength, '\0');
        glGetShaderInfoLog(shader, logLength, nullptr, log.data());
        
        throw std::runtime_error("Shader compilation failed:\n" + log);
    }
}

void Shader::checkProgram(GLuint program){
    GLint success;

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::string log(logLength, '\0');
        glGetProgramInfoLog(program, logLength, nullptr, log.data());
        
        throw std::runtime_error("Program linking failed:\n" + log);
    }
}