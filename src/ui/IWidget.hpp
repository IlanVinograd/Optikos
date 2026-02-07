#ifndef IWIDGET_H
#define IWIDGET_H

#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

#include "render/IRenderQueue.hpp"
#include "utilities/logger.hpp"
#include "utilities/vec.hpp"
#include "utilities/color.hpp"

namespace Optikos
{
enum class ExpandMode : uint8_t
{
    None   = 0,
    Width  = 1,
    Height = 2,
    Both   = 3
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
    virtual Vec2     getPosition() const   = 0;  // return cord of left top corner
    virtual void     setPosition(Vec2 pos) = 0;  // set cord of left top corner
    virtual uint32_t getWidth() const      = 0;
    virtual uint32_t getHeight() const     = 0;
    virtual bool     getVisible() const    = 0;
    virtual bool     getClickable() const  = 0;
    virtual Color    getColor() const      = 0;

    virtual void updateData() = 0;

    virtual void                             resize(int width, int height) = 0;
    virtual const std::vector<unsigned int>& getIndices() const            = 0;
    virtual const std::vector<float>&        getVertices() const           = 0;

    virtual void       setClickable(bool isClickable) = 0;
    virtual void       setAutoExpand(ExpandMode mode) = 0;
    virtual void       setVisible(bool visible)       = 0;
    virtual ExpandMode isExpand()                     = 0;
    virtual void       setColor(Color color)          = 0;

    virtual void handleEvent() = 0;
    virtual void handleHover(double, double)
    {
    }
    virtual void resetHover()
    {
    }
    virtual bool wantsHoverEvents() const
    {
        return false;
    }

    virtual void render(IRenderQueue& renderQueue)
    {
        if (getVisible())
        {
            DrawCommand cmd;
            cmd.vertices  = getVertices();
            cmd.indices   = getIndices();
            cmd.shaderId  = 0;
            cmd.textureId = 0;
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
        Vec2 pos = getPosition();
        return (pos.x <= x && x <= pos.x + getWidth() && pos.y <= y && y <= pos.y + getHeight());
    }

   private:
};

}  // namespace Optikos

#endif /* IWIDGET_H */