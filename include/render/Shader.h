#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace AbyssCore {
    class Shader{
        public:
            Shader(const char* vertexPath, const char* fragmentPath);
            Shader(std::string vertexCode, std::string fragmentCode, bool isCode);
            ~Shader();

            void use();
            void setMat4(const std::string& name, const glm::mat4& mat);
        private:
            unsigned int ID;
            void checkCompileErrors(unsigned int shader, const std::string type);
        
            
    };


}

#endif // SHADER_H