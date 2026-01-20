#ifndef IWIDGET_H
#define IWIDGET_H

#include <cstdint>
#include <vector>

#include "utilities/vec.hpp"

struct Color
{
    float r;
    float g;
    float b;
    float a;
};

struct RenderData
{
    std::vector<float>        vertices;
    std::vector<unsigned int> indices;
};

class IWidget
{
   public:
    virtual ~IWidget()                                    = default;
    virtual vec2                      getPosition()       = 0;  // return cord of left top corner
    virtual uint32_t                  getWidth() const    = 0;
    virtual uint32_t                  getHeight() const   = 0;
    virtual std::vector<float>        getVertices() const = 0;
    virtual std::vector<unsigned int> getIndices() const  = 0;

   private:
};

#endif /* IWIDGET_H */