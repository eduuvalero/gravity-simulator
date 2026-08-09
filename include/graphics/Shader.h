#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader{
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();
        void use() const;
        void setMat4(const std::string& name, const glm::mat4& matrix);
        void setVec3(const std::string& name, const glm::vec3& value);
        void setFloat(const std::string& name, float value);
        void setInt(const std::string& name, int value);
    private:
        GLuint programID;
        static std::string readFile(const std::string& path);
        static GLuint compileShader(GLenum type, const std::string& source);
        static GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);
        static void checkShader(GLuint shader);
        static void checkProgram(GLuint program);
};