#include "ui/sdk/scrollContainer.hpp"

namespace Optikos
{
ScrollContainer::ScrollContainer(uint32_t width, uint32_t height, Vec2 position, Color color)
    : Container(width, height, position, color)
{
    setHoverDimming(0.5);

    m_isClickable = true;

    updateData();
}

void ScrollContainer::render(IRenderQueue& renderQueue)
{
    if (!m_isVisible) return;

    if (m_dirtyLayout)
    {
        updateData();
        for (auto& w : m_subWidgets) w->updateData();
        m_dirtyLayout = false;
    }

    Container::render(renderQueue);

    DrawCommand scrollCmd;
    scrollCmd.vertices  = m_scrollBarData.vertices;
    scrollCmd.indices   = m_scrollBarData.indices;
    scrollCmd.shaderId  = 0;
    scrollCmd.textureId = 0;
    renderQueue.submit(std::move(scrollCmd));
}

void ScrollContainer::updateData()
{
    Container::updateData();

    if (m_contentDirty)
    {
        m_contentHeight = calcContentHeight();
        m_contentDirty  = false;
    }

    m_scrollLength = calcScrollLength();
    m_scrollPos    = findScroller();

    m_scrollBarData.indices = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};

    if (m_useVerticalLayout)
    {
        m_scrollBarData.vertices = {
            {m_position.x + m_width, m_position.y, m_scrollerBarColor.r, m_scrollerBarColor.g,
             m_scrollerBarColor.b, m_scrollerBarColor.a, 0, 0, m_clip.xMin, m_clip.xMax,
             m_clip.yMin, m_clip.yMax},
            {m_position.x + m_width, m_position.y + m_height, m_scrollerBarColor.r,
             m_scrollerBarColor.g, m_scrollerBarColor.b, m_scrollerBarColor.a, 0, 0, m_clip.xMin,
             m_clip.xMax, m_clip.yMin, m_clip.yMax},
            {m_position.x + m_width - m_scrollBarWidth, m_position.y + m_height,
             m_scrollerBarColor.r, m_scrollerBarColor.g, m_scrollerBarColor.b, m_scrollerBarColor.a,
             0, 0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},
            {m_position.x + m_width - m_scrollBarWidth, m_position.y, m_scrollerBarColor.r,
             m_scrollerBarColor.g, m_scrollerBarColor.b, m_scrollerBarColor.a, 0, 0, m_clip.xMin,
             m_clip.xMax, m_clip.yMin, m_clip.yMax},

            {m_position.x + m_width, m_position.y + m_scrollPos, m_scrollerColor.r,
             m_scrollerColor.g, m_scrollerColor.b, m_scrollerColor.a, 0, 0, m_clip.xMin,
             m_clip.xMax, m_clip.yMin, m_clip.yMax},
            {m_position.x + m_width, m_position.y + m_scrollPos + m_scrollLength, m_scrollerColor.r,
             m_scrollerColor.g, m_scrollerColor.b, m_scrollerColor.a, 0, 0, m_clip.xMin,
             m_clip.xMax, m_clip.yMin, m_clip.yMax},
            {m_position.x + m_width - m_scrollWidth, m_position.y + m_scrollPos + m_scrollLength,
             m_scrollerColor.r, m_scrollerColor.g, m_scrollerColor.b, m_scrollerColor.a, 0, 0,
             m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},
            {m_position.x + m_width - m_scrollWidth, m_position.y + m_scrollPos, m_scrollerColor.r,
             m_scrollerColor.g, m_scrollerColor.b, m_scrollerColor.a, 0, 0, m_clip.xMin,
             m_clip.xMax, m_clip.yMin, m_clip.yMax}};
    }
    else
    {
        m_scrollBarData.vertices = {
            {m_position.x, m_position.y + m_height - m_scrollBarWidth, m_scrollerBarColor.r,
             m_scrollerBarColor.g, m_scrollerBarColor.b, m_scrollerBarColor.a, 0, 0, m_clip.xMin,
             m_clip.xMax, m_clip.yMin, m_clip.yMax},
            {m_position.x, m_position.y + m_height, m_scrollerBarColor.r, m_scrollerBarColor.g,
             m_scrollerBarColor.b, m_scrollerBarColor.a, 0, 0, m_clip.xMin, m_clip.xMax,
             m_clip.yMin, m_clip.yMax},
            {m_position.x + m_width, m_position.y + m_height, m_scrollerBarColor.r,
             m_scrollerBarColor.g, m_scrollerBarColor.b, m_scrollerBarColor.a, 0, 0, m_clip.xMin,
             m_clip.xMax, m_clip.yMin, m_clip.yMax},
            {m_position.x + m_width, m_position.y + m_height - m_scrollBarWidth,
             m_scrollerBarColor.r, m_scrollerBarColor.g, m_scrollerBarColor.b, m_scrollerBarColor.a,
             0, 0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},

            {m_position.x + m_scrollPos, m_position.y + m_height, m_scrollerColor.r,
             m_scrollerColor.g, m_scrollerColor.b, m_scrollerColor.a, 0, 0, m_clip.xMin,
             m_clip.xMax, m_clip.yMin, m_clip.yMax},
            {m_position.x + m_scrollPos + m_scrollLength, m_position.y + m_height,
             m_scrollerColor.r, m_scrollerColor.g, m_scrollerColor.b, m_scrollerColor.a, 0, 0,
             m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},
            {m_position.x + m_scrollPos + m_scrollLength, m_position.y + m_height - m_scrollWidth,
             m_scrollerColor.r, m_scrollerColor.g, m_scrollerColor.b, m_scrollerColor.a, 0, 0,
             m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},
            {m_position.x + m_scrollPos, m_position.y + m_height - m_scrollWidth, m_scrollerColor.r,
             m_scrollerColor.g, m_scrollerColor.b, m_scrollerColor.a, 0, 0, m_clip.xMin,
             m_clip.xMax, m_clip.yMin, m_clip.yMax}};
    }
}

float ScrollContainer::calcContentHeight()
{
    float max = 0;
    for (auto& w : m_subWidgets)
    {
        float size = (m_useVerticalLayout == true) ? w->getPosition().y + (float) w->getHeight()
                                                   : w->getPosition().x + (float) w->getWidth();
        max        = std::max(max, size);
    }
    return max - ((m_useVerticalLayout == true) ? m_position.y : m_position.x);
}

bool ScrollContainer::handleClick(double x, double y, int action)
{
    if (action == LEFT_CLICK && isInsideGrab(x, y))
    {
        m_onHold = true;
        return true;
    }

    if (action == RELEASE && m_onHold)
    {
        m_onHold = false;
        resetHover();
        return true;
    }

    return Container::handleClick(x, y, action);
}

void ScrollContainer::resetHover()
{
    if (m_onHold) return;

    m_isHover       = false;
    m_scrollerColor = m_originalColor;
    updateData();
}

bool ScrollContainer::wantsHoverEvents() const
{
    return true;
}

void ScrollContainer::handleDrag(double x, double y)
{
    if (!m_onHold)
    {
        Container::handleDrag(x, y);
        return;
    }

    float viewSize   = m_useVerticalLayout ? (float) m_height : (float) m_width;
    float scrollable = m_contentHeight - viewSize;

    if (scrollable <= 0.0f) return;

    float thumbLength = calcScrollLength();
    float trackLength = viewSize - thumbLength;

    float rawPos = m_useVerticalLayout ? (float) y - m_position.y - thumbLength / 2.0f
                                       : (float) x - m_position.x - thumbLength / 2.0f;

    rawPos = std::clamp(rawPos, 0.0f, trackLength);

    float newOffset = (trackLength > 0.0f) ? (rawPos / trackLength) * scrollable : 0.0f;
    float delta     = newOffset - m_scrollOffset;
    m_scrollOffset  = newOffset;

    for (auto& w : m_subWidgets)
    {
        Vec2 pos = w->getPosition();
        if (m_useVerticalLayout)
            pos.y -= delta;
        else
            pos.x -= delta;
        static_cast<Widget*>(w.get())->setPositionSilent(pos);
    }
    m_dirtyLayout = true;
}

void ScrollContainer::handleHover(double x, double y)
{
    Container::handleHover(x, y);

    bool insideGrab = isInsideGrab(x, y);

    if (insideGrab && !m_isHover)
    {
        m_isHover       = true;
        m_scrollerColor = m_dimmed;
        updateData();
    }
    else if (!insideGrab && m_isHover)
    {
        m_isHover       = false;
        m_scrollerColor = m_originalColor;
        updateData();
    }
}

void ScrollContainer::setHoverDimming(float dimming)
{
    assert(0.0f <= dimming && dimming <= 1.0f);
    m_dimmed.r = static_cast<unsigned char>(std::min(m_originalColor.r * dimming, 255.0f));
    m_dimmed.g = static_cast<unsigned char>(std::min(m_originalColor.g * dimming, 255.0f));
    m_dimmed.b = static_cast<unsigned char>(std::min(m_originalColor.b * dimming, 255.0f));
    m_dimmed.a = m_originalColor.a;
}

bool ScrollContainer::isInsideGrab(double x, double y) const
{
    Clip  clip      = getClip();
    float scrollPos = findScroller();

    if (m_useVerticalLayout)
    {
        bool inSlider =
            (m_position.x + m_width - m_scrollWidth <= x && x <= m_position.x + m_width &&
             m_position.y + scrollPos <= y && y <= m_position.y + scrollPos + m_scrollLength);

        bool inClip = (clip.xMin <= x && x <= clip.xMax && clip.yMin <= y && y <= clip.yMax);

        return inSlider && inClip;
    }
    else
    {
        bool inSlider =
            (m_position.x + scrollPos <= x && x <= m_position.x + scrollPos + m_scrollLength &&
             m_position.y + m_height - m_scrollWidth <= y && y <= m_position.y + m_height);

        bool inClip = (clip.xMin <= x && x <= clip.xMax && clip.yMin <= y && y <= clip.yMax);

        return inSlider && inClip;
    }
}

float ScrollContainer::calcScrollLength() const
{
    float viewSize = m_useVerticalLayout ? (float) m_height : (float) m_width;

    if (m_contentHeight <= 0.0f || m_contentHeight <= viewSize) return viewSize;

    float ratio       = viewSize / m_contentHeight;
    float trackLength = viewSize;
    return std::max(trackLength * ratio, m_scrollBarWidth * 2.0f);
}

float ScrollContainer::findScroller() const
{
    float viewSize   = m_useVerticalLayout ? (float) m_height : (float) m_width;
    float scrollable = m_contentHeight - viewSize;

    if (scrollable <= 0.0f) return 0.0f;

    float thumbLength = calcScrollLength();
    float trackLength = viewSize - thumbLength;

    return std::clamp(m_scrollOffset / scrollable, 0.0f, 1.0f) * trackLength;
}

void ScrollContainer::setScrollBarColor(Color color)
{
    m_scrollerBarColor = color;
    updateData();
}

void ScrollContainer::setScrollThumbColor(Color color)
{
    m_originalColor = color;
    m_scrollerColor = color;
    setHoverDimming(0.5f);
    updateData();
}

void ScrollContainer::setScrollBarWidth(float width)
{
    m_scrollBarWidth = width;
}

void ScrollContainer::setScrollThumbWidth(float width)
{
    m_scrollWidth = width;
}
}  // namespace Optikos