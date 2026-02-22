#include "ui/sdk/container.hpp"

namespace Optikos
{
Container::Container(uint32_t width, uint32_t height, Vec2 position, Color color, bool isVisible)
    : Widget(width, height, position, isVisible, color)
{
    updateData();
    m_data.indices = {0, 1, 2, 2, 3, 0};
}

void Container::render(Optikos::IRenderQueue& renderQueue)
{
    IWidget::render(renderQueue);
    updateLayout();
    for (auto& subWidget : m_subWidgets)
    {
        subWidget->render(renderQueue);
    }
}

void Container::updateData()
{
    Clip containerClip = {m_position.x, m_position.x + m_width, m_position.y,
                          m_position.y + m_height};
    setClip(containerClip);

    m_data.vertices = {
        {m_position.x, m_position.y, m_color.r, m_color.g, m_color.b, m_color.a, 0, 0, m_clip.xMin,
         m_clip.xMax, m_clip.yMin, m_clip.yMax},
        {m_position.x + m_width, m_position.y, m_color.r, m_color.g, m_color.b, m_color.a, 0, 0,
         m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},
        {m_position.x + m_width, m_position.y + m_height, m_color.r, m_color.g, m_color.b,
         m_color.a, 0, 0, m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax},
        {m_position.x, m_position.y + m_height, m_color.r, m_color.g, m_color.b, m_color.a, 0, 0,
         m_clip.xMin, m_clip.xMax, m_clip.yMin, m_clip.yMax}};
}

bool Container::handleClick(double x, double y, int action)
{
    // if (x < m_clip.xMin || x > m_clip.xMax || y < m_clip.yMin || y > m_clip.yMax)
    // {
    //     return false;
    // }

    for (auto it = m_subWidgets.rbegin(); it != m_subWidgets.rend(); ++it)
    {
        (*it)->handleClick(x, y, action);
    }

    if (getClickable() && isInside(x, y))
    {
        handleEvent();  // Currently Container don't have any events like drag etc...
        return true;
    }

    return false;
}

void Container::setPosition(Vec2 pos)
{
    m_position = pos;

    updateData();

    m_needsLayout = true;
}

const std::vector<Vertex>& Container::getVertices() const
{
    return m_data.vertices;
}

const std::vector<unsigned int>& Container::getIndices() const
{
    return m_data.indices;
}

void Container::resize(int width, int height)
{
    m_width  = width;
    m_height = height;

    updateData();

    m_needsLayout = true;
}

void Container::handleEvent()
{
    return; /* stub */
}

void Container::updateLayout()
{
    if (!m_needsLayout) return;
    for (int i = 0; i < m_subWidgets.size(); i++)
    {
        alignWidget(m_subWidgets[i].get(), i);
    }
    m_needsLayout = false;
}

void Container::setAlignment(AlignMode mode)
{
    if (m_alignmentMode != mode)
    {
        m_alignmentMode = mode;
        m_needsLayout   = true;
    }
}

void Container::setInterval(int interval)
{
    if (m_interval != interval)
    {
        m_interval    = interval;
        m_needsLayout = true;
    }
}

void Container::setOffset(int offset)
{
    assert(offset >= 0);
    if (m_offset != offset)
    {
        m_offset      = offset;
        m_needsLayout = true;
    }
}

void Container::alignWidget(IWidget* subWidget, int index)
{
    Vec2  newPos;
    float primaryPos = 0.0f;
    float secondaryPos = 0.0f;

    float totalSize = 0.0f;
    for (const auto& widget : m_subWidgets)
    {
        totalSize +=
            static_cast<float>(m_useVerticalLayout ? widget->getHeight() : widget->getWidth());
    }
    if (m_subWidgets.size() > 1)
    {
        totalSize += static_cast<float>((m_subWidgets.size() - 1) * m_interval);
    }

    float prefixSize = 0.0f;
    for (int i = 0; i < index; ++i)
    {
        prefixSize += static_cast<float>(m_useVerticalLayout ? m_subWidgets[i]->getHeight()
                                                             : m_subWidgets[i]->getWidth());
        if (i > 0)
        {
            prefixSize += static_cast<float>(m_interval);
        }
    }
    if (index > 0)
    {
        prefixSize += static_cast<float>(m_interval);
    }

    float containerSize  = static_cast<float>(m_useVerticalLayout ? m_height : m_width);
    float containerStart = m_useVerticalLayout ? m_position.y : m_position.x;

    switch (m_alignmentMode)
    {
        case AlignMode::Left:
            primaryPos = containerStart + m_offset + prefixSize;
            break;
        case AlignMode::Middle:
        {
            float startPos = containerStart + (containerSize / 2.0f) - (totalSize / 2.0f);
            primaryPos     = startPos + prefixSize;
        }
        break;
        case AlignMode::Right:
        {
            float startPos = containerStart + containerSize - totalSize - m_offset;
            primaryPos     = startPos + prefixSize;
        }
        break;
        default:
            primaryPos = containerStart + m_offset + prefixSize;
            break;
    }

    if (m_useVerticalLayout)
    {
        float widgetWidth = static_cast<float>(subWidget->getWidth());
        switch (m_alignmentMode)
        {
            case AlignMode::Left:
                secondaryPos = m_position.x + m_offset;
                break;
            case AlignMode::Middle:
                secondaryPos = m_position.x + (m_width / 2.0f) - (widgetWidth / 2.0f);
                break;
            case AlignMode::Right:
                secondaryPos = m_position.x + m_width - widgetWidth - m_offset;
                break;
            default:
                secondaryPos = m_position.x + m_offset;
                break;
        }
        newPos = {secondaryPos, primaryPos};
    }
    else
    {
        float widgetHeight = static_cast<float>(subWidget->getHeight());
        switch (m_alignmentMode)
        {
            case AlignMode::Left:
                secondaryPos = m_position.y + m_offset;
                break;
            case AlignMode::Middle:
                secondaryPos = m_position.y + (m_height / 2.0f) - (widgetHeight / 2.0f);
                break;
            case AlignMode::Right:
                secondaryPos = m_position.y + m_height - widgetHeight - m_offset;
                break;
            default:
                secondaryPos = m_position.y + m_offset;
                break;
        }
        newPos = {primaryPos, secondaryPos};
    }

    subWidget->setPosition(newPos);

    Clip containerClip = {m_position.x, m_position.x + m_width, m_position.y,
                          m_position.y + m_height};

    Clip finalClip;
    finalClip.xMin = std::max(containerClip.xMin, m_clip.xMin);
    finalClip.xMax = std::min(containerClip.xMax, m_clip.xMax);
    finalClip.yMin = std::max(containerClip.yMin, m_clip.yMin);
    finalClip.yMax = std::min(containerClip.yMax, m_clip.yMax);

    subWidget->setClip(finalClip);
    subWidget->updateData();
}

bool Container::wantsHoverEvents() const
{
    for (const auto& widget : m_subWidgets)
    {
        if (widget->wantsHoverEvents()) return true;
    }
    return false;
}

bool Container::wantsGetInput() const
{
    for (const auto& widget : m_subWidgets)
    {
        if (widget->wantsGetInput()) return true;
    }
    return false;
}

void Container::passInput(unsigned int codepoint)
{
    for (auto& subWidget : m_subWidgets)
    {
        if (!subWidget->wantsGetInput()) continue;

        subWidget->passInput(codepoint);
    }
}

void Container::handleHover(double x, double y)
{
    bool foundHover = false;

    for (auto& subWidget : m_subWidgets)
    {
        if (!subWidget->wantsHoverEvents())
        {
            subWidget->resetHover();
            continue;
        }

        if (!foundHover && subWidget->isInside(x, y))
        {
            subWidget->handleHover(x, y);
            foundHover = true;
        }
        else
        {
            subWidget->resetHover();
        }
    }
}

void Container::resetHover()
{
    for (auto& subWidget : m_subWidgets)
    {
        subWidget->resetHover();
    }
}

void Container::setVisible(bool visible)
{
    for (auto& subWidget : m_subWidgets)
    {
        subWidget->setVisible(visible);
    }

    m_isVisible = visible;
}

void Container::handleDrag(double x, double y)
{
    for (auto& subWidget : m_subWidgets)
    {
        subWidget->handleDrag(x, y);
    }
}

void Container::useVerticalLayout(bool isVertical)
{
    m_useVerticalLayout = isVertical;
    m_needsLayout       = true;
}

}  // namespace Optikos