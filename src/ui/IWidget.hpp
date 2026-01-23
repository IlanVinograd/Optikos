#ifndef IWIDGET_H
#define IWIDGET_H

#include <cstdint>
#include <functional>

#include <vector>

#include "utilities/vec.hpp"

struct Color
{
    float r;
    float g;
    float b;
    float a;
};

struct Attributes
{
    bool                  isVisible;
    vec2                  position;
    uint32_t              width;
    uint32_t              height;
    std::function<void()> eventCallback = nullptr;
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
    virtual vec2                      getPosition() const = 0;  // return cord of left top corner
    virtual uint32_t                  getWidth() const    = 0;
    virtual uint32_t                  getHeight() const   = 0;
    virtual const std::vector<float>& getVertices() const = 0;
    virtual bool                      getVisible() const  = 0;
    virtual const std::vector<unsigned int>& getIndices() const = 0;
    virtual void                             handleEvent()      = 0;

   private:
};

#endif /* IWIDGET_H */