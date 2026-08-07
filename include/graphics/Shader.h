#pragma once

#include <string>
#include <glad/glad.h>

class Shader{
    private:
        GLuint programID;
        static std::string readFile(const std::string& path);
        static GLuint compileShader(GLenum type, const std::string& source);
        static GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);
        static void checkShader(GLuint shader);
        static void checkProgram(GLuint program);
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader() { glDeleteProgram(programID); };
        void use() const { glUseProgram(programID); };
};