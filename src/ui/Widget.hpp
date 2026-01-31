#ifndef WIDGET_H
#define WIDGET_H

#include "ui/IWidget.hpp"

class Widget : public IWidget
{
   public:
    Widget(uint32_t width, uint32_t height, vec2 position, bool isVisible = true)
        : m_position(position),
          m_width(width),
          m_height(height),
          m_isVisible(isVisible),
          m_isExpand(ExpandMode::None),
          m_isClickable(false)
    {
    }

    virtual ~Widget() = default;

    inline vec2 getPosition() const override
    {
        return m_position;
    }
    inline void setPosition(vec2 pos) override
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

    inline void updateData() override
    {
        return; /* stub */
    }

   protected:
    vec2       m_position;
    uint32_t   m_width;
    uint32_t   m_height;
    bool       m_isVisible;
    ExpandMode m_isExpand;
    bool       m_isClickable;
};

#endif /* WIDGET_H */