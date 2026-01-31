#include "shader/GLSL/GLShader.hpp"

unsigned int GLShader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id  = glCreateShader(type);
    
    assert(!source.empty());
    const char*  src = source.c_str();
    
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TODO: Error handle
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* massage = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, massage);

        LOG_WARN("[compileShader] Failed to compile shader, type: " +
                     std::string(type == GL_VERTEX_SHADER ? "vertex " : "fragment ") +
                     "Error: " + std::string(massage),
                 "log");

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int GLShader::createShader(const std::string& vertexShader,
                                    const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs      = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs      = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

ShaderSouces GLShader::parseShader(const std::string& file)
{
    std::fstream      stream(file);
    ShaderType        type = ShaderType::NONE;
    std::string       line;
    std::stringstream ss[2];
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[static_cast<int>(type)] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}