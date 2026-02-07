#ifndef WIDGET_H
#define WIDGET_H

#include "ui/IWidget.hpp"

namespace Optikos
{
class Widget : public IWidget
{
   public:
    Widget(uint32_t width, uint32_t height, Vec2 position, bool isVisible = true,
           Color color = Color{0.0, 50.0, 150.0, 255.0})
        : m_position(position),
          m_width(width),
          m_height(height),
          m_isVisible(isVisible),
          m_color(color),
          m_isExpand(ExpandMode::None),
          m_isClickable(false)
    {
    }

    virtual ~Widget() = default;

    inline Vec2 getPosition() const override
    {
        return m_position;
    }
    inline void setPosition(Vec2 pos) override
    {
        m_position = pos;
    }
    inline uint32_t getWidth() const override
    {
        return m_width;
    }
    inline uint32_t getHeight() const override
    {
        return m_height;
    }
    inline bool getVisible() const override
    {
        return m_isVisible;
    }

    inline Color getColor() const override
    {
        return m_color;
    }

    inline bool getClickable() const override
    {
        return m_isClickable;
    }
    inline ExpandMode isExpand() override
    {
        return m_isExpand;
    }

    inline void setClickable(bool isClickable) override
    {
        m_isClickable = isClickable;
    }

    inline void setAutoExpand(ExpandMode mode) override
    {
        m_isExpand = mode;
    }

    inline void setVisible(bool visible) override
    {
        m_isVisible = visible;
    }

    inline void setColor(Color color) override
    {
        m_color = color;
    }

    inline void updateData() override
    {
        return; /* stub */
    }

   protected:
    Vec2     m_position;
    uint32_t   m_width;
    uint32_t   m_height;
    bool       m_isVisible;
    bool       m_isClickable;
    ExpandMode m_isExpand;
    Color      m_color;
};

}  // namespace Optikos

#endif /* WIDGET_H */