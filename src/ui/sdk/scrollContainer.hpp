#ifndef SCROLLCONTAINER_H
#define SCROLLCONTAINER_H

#include "ui/sdk/container.hpp"

namespace Optikos
{

float constexpr DEFAULT_SCROLL_BAR_WIDTH   = 8.0f;
float constexpr DEFAULT_SCROLL_THUMB_WIDTH = 8.0f;

Color constexpr DEFAULT_SCROLLBAR_COLOR   = {50, 100, 150, 255};
Color constexpr DEFAULT_SCROLLTHUMB_COLOR = {200, 120, 180, 255};

class ScrollContainer : public Container
{
   public:
    ScrollContainer(uint32_t width, uint32_t height, Vec2 position, Color color = {0, 0, 0, 1});

    template <typename T>
    T* addSubWidget(std::unique_ptr<T> widget)
    {
        m_contentDirty = true;
        return Container::addSubWidget(std::move(widget));
    }

    void render(IRenderQueue& renderQueue) override;
    void updateData() override;
    void handleDrag(double x, double y) override;
    bool handleClick(double x, double y, int action) override;
    bool wantsHoverEvents() const override;
    void resetHover() override;
    void handleHover(double x, double y) override;

    void setScrollBarWidth(float width);
    void setScrollThumbWidth(float width);
    void setScrollBarColor(Color color);
    void setScrollThumbColor(Color color);

   private:
    bool  isInsideGrab(double x, double y) const;
    void  setHoverDimming(float dimming);
    float findScroller() const;
    float calcScrollLength() const;
    float calcContentHeight();

    float m_scrollOffset  = 0.0f;
    float m_contentHeight = 0.0f;

    float m_scrollBarWidth = DEFAULT_SCROLL_BAR_WIDTH;
    float m_scrollWidth    = DEFAULT_SCROLL_THUMB_WIDTH;
    float m_scrollPos      = 0.0f;
    float m_scrollLength   = 0.0f;

    RenderData m_scrollBarData;

    Color m_scrollerBarColor = DEFAULT_SCROLLBAR_COLOR;
    Color m_originalColor    = DEFAULT_SCROLLTHUMB_COLOR;
    Color m_scrollerColor    = DEFAULT_SCROLLTHUMB_COLOR;
    Color m_dimmed;

    bool m_onHold       = false;
    bool m_isHover      = false;
    bool m_dirtyLayout  = false;
    bool m_contentDirty = false;
};

}  // namespace Optikos

#endif /* SCROLLCONTAINER_H */