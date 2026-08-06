#pragma one

#include <string>
#include <glad/glad.h>

class Shader{
    private:
        GLuint programID;
        std::string readFile(const std::string& path);
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();
        void use() const;
};