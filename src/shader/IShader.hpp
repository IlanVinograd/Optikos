#ifndef ISHADER_H
#define ISHADER_H

#include <string>

enum class ShaderType
{
    NONE     = -1,
    VERTEX   = 0,
    FRAGMENT = 1
};

struct ShaderSouces
{
    std::string vertexSource;
    std::string fragmentSource;
};

class IShader
{
   public:
    virtual ~IShader()                                                               = default;
    virtual unsigned int compileShader(unsigned int type, const std::string& source) = 0;
    virtual unsigned int createShader(const std::string& vertexShader,
                                      const std::string& fragmentShader)             = 0;
    virtual ShaderSouces parseShader(const std::string& file)                        = 0;
};

#endif /* ISHADER_H */