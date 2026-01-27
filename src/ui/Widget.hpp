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
          m_isExpand(0),
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
    inline int isExpand() override
    {
        return m_isExpand;
    }

    inline void setClickable(bool isClickable) override
    {
        m_isClickable = isClickable;
    }

    inline void setAutoExpand(int isExpand) override
    {
        assert(isExpand >= 0 && isExpand <= 3);
        /* 0 = don't expand, 1 = expand only width, 2 = expand only height, 3 = expand both */  // TODO: make enums/defines
        m_isExpand = isExpand;
    }

    inline void updateVertices() override
    {
        return; /* stub */
    }

   protected:
    vec2     m_position;
    uint32_t m_width;
    uint32_t m_height;
    bool     m_isVisible;
    int      m_isExpand;
    bool     m_isClickable;
};

#endif /* WIDGET_H */