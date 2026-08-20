#include "graphics/Shader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

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
}

Shader::~Shader() { 
    glDeleteProgram(programID); 
}

void Shader::use() const { 
    glUseProgram(programID); 
}

GLuint Shader::compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);

#ifdef __EMSCRIPTEN__
    std::string shaderSourceText = source;

    const std::string desktopVersion = "#version 330 core";
    const std::string webVersion = "#version 300 es";

    if (shaderSourceText.rfind(desktopVersion, 0) == 0) {
        shaderSourceText.replace(0, desktopVersion.size(), webVersion);
    }

    const std::size_t versionEnd = shaderSourceText.find('\n');

    if (versionEnd != std::string::npos) {
        shaderSourceText.insert(versionEnd + 1, "precision highp float;\n");
    }

    const char* shaderSource = shaderSourceText.c_str();

#else
    const char* shaderSource = source.c_str();
#endif
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

void Shader::setMat4(const std::string& name, const glm::mat4& matrix){
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec3(const std::string& name, const glm::vec3& value){
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setFloat(const std::string& name, float value){
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value){
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}