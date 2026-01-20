#ifndef GLSHADER_H
#define GLSHADER_H

#include <fstream>
#include <sstream>

#include "shader/IShader.hpp"
#include "utilities/logger.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class GLShader : public IShader
{
   public:
    ~GLShader() = default;
    unsigned int compileShader(unsigned int type, const std::string& source) override;
    unsigned int createShader(const std::string& vertexShader,
                              const std::string& fragmentShader) override;
    ShaderSouces parseShader(const std::string& file) override;

   private:
};

#endif /* GLSHADER_H */