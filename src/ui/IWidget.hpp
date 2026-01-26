#ifndef IWIDGET_H
#define IWIDGET_H

#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

#include "render/IRenderQueue.hpp"
#include "utilities/logger.hpp"
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
    virtual ~IWidget()                     = default;
    virtual vec2     getPosition() const   = 0;  // return cord of left top corner
    virtual void     setPosition(vec2 pos) = 0;  // set cord of left top corner
    virtual uint32_t getWidth() const      = 0;
    virtual uint32_t getHeight() const     = 0;
    virtual bool     getVisible() const    = 0;
    virtual bool     getClickable() const  = 0;

    virtual void                             resize(int width, int height) = 0;
    virtual const std::vector<unsigned int>& getIndices() const            = 0;
    virtual const std::vector<float>&        getVertices() const           = 0;

    virtual void setClickable(bool isClickable) = 0;
    virtual void setAutoExpand(int isExpand)    = 0;
    virtual int  isExpand()                     = 0;

    virtual void handleEvent() = 0;

    virtual void render(Optikos::IRenderQueue& renderQueue)
    {
        if (getVisible())
        {
            Optikos::DrawCommand cmd;
            cmd.vertices = getVertices();
            cmd.indices  = getIndices();
            cmd.shaderId = 0;
            renderQueue.submit(std::move(cmd));
        }
    }

    virtual bool handleClick(double x, double y)
    {
        if (getClickable() && isInside(x, y))
        {
            handleEvent();
            return true;
        }
        return false;
    }

    bool isInside(double x, double y) const
    {
        vec2 pos = getPosition();
        return (pos.x <= x && x <= pos.x + getWidth() && pos.y <= y && y <= pos.y + getHeight());
    }

   private:
};

#endif /* IWIDGET_H */